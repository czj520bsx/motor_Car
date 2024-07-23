# Untitled - By: QY - 周一 9月 18 2023

from machine import UART
from fpioa_manager import fm
import time
import audio
from fpioa_manager import fm
from Maix import I2S, GPIO
import sensor, image, lcd


# ---------------------------------------- #
# 函数原型: Audio_Init()
# 函数功能: 音频设备初始化
# 函数参数: 无
# 返回值: 音频设备
# ---------------------------------------- #
def Audio_Init():
    # register i2s(i2s0) pin
    fm.register(12, fm.fpioa.I2S0_OUT_D1)  # in
    fm.register(14, fm.fpioa.I2S0_SCLK)  # bclk
    fm.register(24, fm.fpioa.I2S0_WS)  # lrc

    # init i2s(i2s0)
    wav_dev = I2S(I2S.DEVICE_0)
    return wav_dev



# ------------------------------------功能----------------------------------------- #
# ---------------------------------------- #
# 函数原型: Audio_Play(wav_path)
# 函数功能: 播放音频
# 函数参数: 音频的地址
# 返回值: 无
# ---------------------------------------- #
def Audio_Play(wav_path):
    global wav_dev

    # init audio
    player = audio.Audio(path=wav_path)  # 其他音频有问题，这里播放音频必须有选择。
    player.volume(100)

    # read audio info
    wav_info = player.play_process(wav_dev)
    print("wav file head information: ", wav_info)

    # config i2s according to audio info
    wav_dev.channel_config(wav_dev.CHANNEL_1, I2S.TRANSMITTER, resolution=I2S.RESOLUTION_32_BIT,
                           cycles=I2S.SCLK_CYCLES_32, align_mode=I2S.STANDARD_MODE)
    wav_dev.set_sample_rate(wav_info[1])

    # loop to play audio
    while True:
        ret = player.play()
        if ret == None:
            print("format error")
            break
        elif ret == 0:
            print("end")
            break
    player.finish()

def Sensor_Init():
    # 摄像头初始化
    sensor.reset()
    sensor.set_framesize(sensor.QVGA)
    sensor.set_pixformat(sensor.RGB565)
    #sensor.skip_frames(time = 2000)

    # 设置镜像翻转
    sensor.set_hmirror(1)   # 纵向的镜像翻转
    sensor.set_vflip(1)     # 横向的镜像翻转

    sensor.run(1)

def Sensor_Check(uart, node):
    cmd = [0xb1, 0xb1, node]
    # 3、拍摄一帧图片
    Audio_Play("check.wav")
    img = sensor.snapshot()
    lcd.display(img)

    blobs = img.find_blobs([threshold1], area_threshold=100, pixels_threshold=300)
    if len(blobs)>0:
        # x, y, w, h, cx, cy
        for b in blobs:
            # 描绘出物体的矩形框
            img.draw_rectangle(b[0:4])

            # 描绘出物体的中心点
            img.draw_cross(b[5], b[6])
        lcd.display(img)
        Audio_Play("find.wav")

        img_compress = img.compress(10)# 压缩图片
        img_size = img_compress.size()
        print(img_size)
        cmd = bytes(cmd) + img_size.to_bytes(2, "")
        print(cmd)
        uart.write(cmd)
        uart.write(img_compress.to_bytes(img_size, ""))
        Audio_Play("upload_over.wav")
    else:
        Audio_Play("nofind.wav")

def Sensor_Unauto_pic(uart, node):
    cmd = [0xb1, 0xb1, node]
    # 3、拍摄一帧图片
    img = sensor.snapshot()
    lcd.display(img)

    img_compress = img.compress(10)# 压缩图片
    img_size = img_compress.size()
    print(img_size)
    cmd = bytes(cmd) + img_size.to_bytes(2, "")
    print(cmd)
    uart.write(cmd)
    uart.write(img_compress.to_bytes(img_size, ""))
    Audio_Play("upload_over.wav")


# 注册引脚功能
fm.register(6, fm.fpioa.UART1_RX)
fm.register(8, fm.fpioa.UART1_TX)

# 串口初始化
uart = UART(UART.UART1, 9600, 8, None, 1, timeout = 100, read_buf_len = 4096)

# 摄像头初始化
Sensor_Init()

# 色块阈值
threshold1 = (0, 100, -128, -47, -128, 127)
lcd.init(color=lcd.RED) # lcd初始化

wav_dev = Audio_Init()

flag_recv = 0
flag_mode = 0

while 1:
    if uart.any():# 判断是否有数据
        recv = uart.readchar()# 接收一个字节
        print("%x" %(recv))
        if recv == 0xb1:
            flag_recv = 1
        elif recv == 0x1b and flag_recv == 1:
            flag_recv = 2
        elif recv == 0x11 and flag_recv == 2:
            flag_recv = 3
            flag_mode = 1
        elif recv == 0x22 and flag_recv == 2:
            flag_recv = 3
            flag_mode = 2
        elif flag_mode == 1 and flag_recv == 3:# 小车启动/停止
            if recv == 0x0:
                Audio_Play("check_start.wav")
            elif recv == 0x1:
                Audio_Play("check_stop.wav")
            elif recv == 0x2:
                # 手动拍照
                Audio_Play("/sd/pic_start.wav")
                Sensor_Unauto_pic(uart, 0x00)
            flag_mode = 0;
            flag_recv = 0;
        elif flag_mode == 2 and flag_recv == 3:# 节点检测
            if recv == 0x1:
                Audio_Play("d1.wav")
                Sensor_Check(uart, recv)
                Audio_Play("continue.wav")
            elif recv == 0x2:
                Audio_Play("d2.wav")
                Sensor_Check(uart, recv)
                Audio_Play("continue.wav")
            elif recv == 0x3:
                Audio_Play("d3.wav")
                Sensor_Check(uart, recv)
                Audio_Play("continue.wav")
            elif recv == 0x4:
                Audio_Play("d4.wav")
                Sensor_Check(uart, recv)
                Audio_Play("check_stop.wav")
            flag_mode = 0
            flag_recv = 0
        else:
            flag_recv = 0;



