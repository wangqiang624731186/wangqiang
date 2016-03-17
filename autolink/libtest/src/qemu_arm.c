/*************************************************************************
test_mcu.c
************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include"autolink_mcu.h"


static void autolink_deal_camera(autolink_camera_type_em type,
                                 autolink_camera_state_em state,
                                 void* userdata)
{
    if(type == CAMERA_REAR)
    {
        printf("倒车摄像头:");
    }

    if(state == CAMERA_IN)
    {
        printf("信号进入\n");
    }
    else if(state == CAMERA_OUT)
    {
        printf("信号退出\n");
    }

    return;
}

static void autolink_deal_acc(autolink_acc_state_em state,void* userdata)
{
    if(state == ACC_IN)
    {
        printf("ACC进入\n");
    }
    else if(state == ACC_OUT)
    {
        printf("ACC退出\n");
    }

    return;
}

static void autolink_deal_valid_source(int source, void* userdata)
{
    printf("有效信号源:");
    if(1 == CHECK_SOURCE(source,VALID_SOURCE_STUB))
    {
        printf(" stub");
    }

    if(1 == CHECK_SOURCE(source,VALID_SOURCE_RADIO))
    {
        printf(" radio");
    }

    if(1 == CHECK_SOURCE(source,VALID_SOURCE_AUDIO))
    {
        printf(" audio");
    }

    if(1 == CHECK_SOURCE(source,VALID_SOURCE_MEDIA))
    {
        printf(" media");
    }

    if(1 == CHECK_SOURCE(source,VALID_SOURCE_DVR))
    {
        printf(" dvr");
    }

    if(1 == CHECK_SOURCE(source,VALID_SOURCE_AUX))
    {
        printf(" aux");
    }

    if(1 == CHECK_SOURCE(source,VALID_SOURCE_BTMUSIC))
    {
        printf(" btmusic");
    }

    if(1 == CHECK_SOURCE(source,VALID_SOURCE_SYNC))
    {
        printf(" sync");
    }

    printf("\n");
}

static void autolink_deal_init(autolink_init_state_em state,void* userdata)
{
    if(state == INIT_COMPLETE)
    {
        printf("初始化数据完成\n");
    }

    return;
}

static void autolink_deal_work_ui_source(autolink_source_st source, void* userdata)
{
    printf("当前工作源的界面:");
    switch(source.work_ui_source_current)
    {
        case UI_SOURCE_STUB:
            printf(" stub");
            break;
        case UI_SOURCE_RADIO:
            printf(" radio");
            break;
        case UI_SOURCE_USB:
            printf(" usb");
            break;
        case UI_SOURCE_SD:
            printf(" sd");
            break;
        case UI_SOURCE_DVR:
            printf(" dvr");
            break;
        case UI_SOURCE_AUX:
            printf(" aux");
            break;
        case UI_SOURCE_BTMUSIC:
            printf(" btmusic");
            break;
        case UI_SOURCE_SYNC:
            printf(" sync");
            break;
        default:
            printf("UNKOWN UI\n");
            break;
    }

    printf("\n");

    printf("上一个工作源的界面:");
    switch(source.work_ui_source_ui_previous)
    {
        case UI_SOURCE_STUB:
            printf(" stub");
            break;
        case UI_SOURCE_RADIO:
            printf(" radio");
            break;
        case UI_SOURCE_USB:
            printf(" usb");
            break;
        case UI_SOURCE_SD:
            printf(" sd");
            break;
        case UI_SOURCE_DVR:
            printf(" dvr");
            break;
        case UI_SOURCE_AUX:
            printf(" aux");
            break;
        case UI_SOURCE_BTMUSIC:
            printf(" btmusic");
            break;
        case UI_SOURCE_SYNC:
            printf(" sync");
            break;
        default:
            printf("UNKOWN UI\n");
            break;
    }
    printf("\n");

    printf("工作状态窗口界面:");
    if(1 == CHECK_SOURCE(source.work_ui_user_state,USER_STATE_NORMAL))
    {
        printf(" normal");
    }

    if(1 == CHECK_SOURCE(source.work_ui_user_state,USER_STATE_SETUP))
    {
        printf(" setup");
    }

    if(1 == CHECK_SOURCE(source.work_ui_user_state,USER_STATE_GPS))
    {
        printf(" gps");
    }

    if(1 == CHECK_SOURCE(source.work_ui_user_state,USER_STATE_BACKSIGHT))
    {
        printf(" backsight");
    }

    if(1 == CHECK_SOURCE(source.work_ui_user_state,USER_STATE_PHOTO))
    {
        printf(" phote");
    }

    if(1 == CHECK_SOURCE(source.work_ui_user_state,USER_STATE_MP3))
    {
        printf(" mp3");
    }

    if(1 == CHECK_SOURCE(source.work_ui_user_state,USER_STATE_MP4))
    {
        printf(" mp4");
    }

    if(1 == CHECK_SOURCE(source.work_ui_user_state,USER_STATE_BT))
    {
        printf(" bt");
    }

    printf("\n");

    printf("当前是否是主界面:");
    if(source.work_ui_source_ishome == UI_ISHOME_TRUE)
    {
        printf("是");
    }
    else
    {
        printf("否");
    }
    printf("\n");
}


static void autolink_deal_system_volume(unsigned int volume,
                                        autolink_volume_bar_show_em show,
                                        void* userdata)
{
    printf("系统音量:%d",volume);
    if( VOLUME_BAR_SHOW_FALSE == show)
    {
        printf(" 不显示音量条\n");
    }
    else if( VOLUME_BAR_SHOW_TRUE == show)
    {
        printf(" 显示音量条\n");
    }

    return;
}

static void autolink_deal_btphone_volume(unsigned int volume,
                                         autolink_volume_bar_sync_em sync,
                                         void* userdata)
{
    printf("蓝牙通话音量:%d",volume);
    if( VOLUME_BAR_SYNC_FALSE == sync)
    {
        printf(" 不同步系统音量条\n");
    }
    else if( VOLUME_BAR_SYNC_TRUE == sync)
    {
        printf(" 同步系统音量条\n");
    }

    return;
}

static void autolink_deal_mute_volume(autolink_volume_mute_em mute,
                                      void* userdata)
{
    if( VOLUME_MUTE_TRUE == mute)
    {
        printf("开启静音\n");
    }
    else if( VOLUME_MUTE_FALSE == mute)
    {
        printf("关闭静音\n");
    }
    return;
}

static void autolink_deal_time_value(autolink_time_st time,
                                     void* userdata)
{

    printf("当前时间:%d-%d-%d-%d-%d-%d\n",time.year,time.mon,time.day,
           time.hour,time.min,time.sec);
    return;
}

static void autolink_deal_time_format(autolink_time_st time,
                                      void* userdata)
{

    if( TIME_FORMAT_12H == time.time_format)
    {
        printf("当前时间为12H制\n");
    }
    else if( TIME_FORMAT_24H == time.time_format)
    {
        printf("当前时间为24H制\n");
    }

    return;
}

static void autolink_deal_lcd_state(autolink_lcd_state_em state,
                                    void* userdata)
{

    if( LCD_STATE_ON == state)
    {
        printf("点亮LCD\n");
    }
    else if( LCD_STATE_OFF == state)
    {
        printf("关闭LCD\n");
    }

    return;
}

static void autolink_deal_radio_mainfreq(autolink_radio_st radio,
                                         void* userdata)
{

    printf("收音:\n");

    if( RADIO_BAND_FM == radio.current.band)
    {
        printf("FM\n");
    }
    else if( RADIO_BAND_AM== radio.current.band)
    {
        printf("AM\n");
    }

    printf("POS=%d\n",radio.current.freq_position);
    printf("FREQ=%f\n",radio.current.freq);

    if( RADIO_SEARCH_UP == radio.search)
    {
        printf("向上搜索\n");
    }
    else if( RADIO_SEARCH_DOWN== radio.search)
    {
        printf("向下搜索\n");
    }
    else if( RADIO_SEARCH_MANUAL== radio.search)
    {
        printf("手动搜索\n");
    }
    else if( RADIO_SEARCH_BROWSE== radio.search)
    {
        printf("浏览搜索\n");
    }

    if( RADIO_ST_SHOW_TRUE == radio.st_show)
    {
        printf("立体声开关显示\n");
    }
    else if( RADIO_ST_SHOW_FALSE== radio.st_show)
    {
        printf("立体声开关ST不显示\n");
    }

    if( RADIO_STFLAG_SHOW_TRUE == radio.stflag_show)
    {
        printf("立体声状态开关显示\n");
    }
    else if( RADIO_STFLAG_SHOW_FALSE== radio.stflag_show)
    {
        printf("立体声状态开关不显示\n");
    }

    if( RADIO_LOC_SHOW_TRUE == radio.loc_show)
    {
        printf("远近程开关显示\n");
    }
    else if( RADIO_LOC_SHOW_FALSE== radio.loc_show)
    {
        printf("远近程开关不显示\n");
    }
    return;
}

static void autolink_deal_radio_savefreq(autolink_radio_st radio,
                                         void* userdata)
{

    printf("收音储存:\n");

    if( RADIO_BAND_FM == radio.save.band)
    {
        printf("FM\n");
    }
    else if( RADIO_BAND_AM== radio.save.band)
    {
        printf("AM\n");
    }

    printf("POS=%d\n",radio.save.freq_position);
    printf("FREQ=%f\n",radio.save.freq);

    return;
}

static void autolink_deal_radio_all_savefreq(autolink_radio_st radio,
                                             void* userdata)
{
    int iter = 0;
    printf("收音已储存:\n");



    while(iter < radio.allsave_count)
    {
        if( RADIO_BAND_FM == radio.allsave[iter].band)
        {
            printf("FM\n");
        }
        else if( RADIO_BAND_AM== radio.allsave[iter].band)
        {
            printf("AM\n");
        }
        printf("FREQ=%f\n",radio.allsave[iter].freq);
        iter++;
    }

    return;
}

static void autolink_deal_eq_state(autolink_eq_st eq,void* userdata)
{

    printf("音效状态: ");
    if( EQ_STATE_BASS == eq.eq_state)
    {
        printf("低音 ");
    }
    else if( EQ_STATE_ALTO== eq.eq_state)
    {
        printf("中音 ");
    }
    else if( EQ_STATE_TREBLE== eq.eq_state)
    {
        printf("高音 ");
    }
    else if( EQ_STATE_FB_BALANCE== eq.eq_state)
    {
        printf("前后平衡 ");
    }
    else if( EQ_STATE_LR_BALANCE== eq.eq_state)
    {
        printf("左右平衡 ");
    }

    printf("%d \n",eq.eq_state_value);

    return;
}

static void autolink_deal_eq_mode(autolink_eq_st eq,void* userdata)
{
    printf("音效模式: ");
    if( EQ_MODE_USER == eq.eq_mode)
    {
        printf("用户 ");
    }
    else if( EQ_MODE_POP== eq.eq_mode)
    {
        printf("流行 ");
    }
    else if( EQ_MODE_CLASSIC== eq.eq_mode)
    {
        printf("古典 ");
    }
    else if( EQ_MODE_ROCK== eq.eq_mode)
    {
        printf("摇滚 ");
    }
    else if( EQ_MODE_JAZZ== eq.eq_mode)
    {
        printf("爵士 ");
    }
    else if( EQ_MODE_CLUB== eq.eq_mode)
    {
        printf("俱乐部 ");
    }
    else if( EQ_MODE_COUNTRY== eq.eq_mode)
    {
        printf("乡村 ");
    }
    else if( EQ_MODE_DANCE== eq.eq_mode)
    {
        printf("舞蹈 ");
    }
    else if( EQ_MODE_GENTLE== eq.eq_mode)
    {
        printf("轻柔 ");
    }
    else if( EQ_MODE_PEACE== eq.eq_mode)
    {
        printf("平和 ");
    }

    printf("\n");
    return;
}

static void autolink_deal_lcd_brightness(autolink_lcd_st lcd,
                                         void* userdata)
{
    printf("亮度:%d\n",lcd.brightness);
    return;
}

static void autolink_deal_lcd_contrast(autolink_lcd_st lcd,
                                       void* userdata)
{
    printf("对比度:%d\n",lcd.contrast);
    return;
}

static void autolink_deal_lcd_hue(autolink_lcd_st lcd,
                                  void* userdata)
{
    printf("色度:%d\n",lcd.hue);
    return;
}

static void autolink_deal_video_mode(autolink_video_mode_em video_mode,
                                     void* userdata)
{
    printf("视频模式:");
    if(VIDEO_MODE_STANDARD == video_mode)
    {
        printf("标准");
    }
    else if(VIDEO_MODE_GENTLE == video_mode)
    {
        printf("柔和");
    }
    else if(VIDEO_MODE_BRIGHT == video_mode)
    {
        printf("明亮");
    }
    else if(VIDEO_MODE_USER == video_mode)
    {
        printf("用户");
    }

    printf("\n");
    return;
}

static void autolink_deal_beep_volume(autolink_volume_st volume,
                                      void* userdata)
{
    printf("蜂鸣器:");
    if(BEEP_VOLUME_OFF == volume.beep_volume)
    {
        printf("关");
    }
    else if(BEEP_VOLUME_ON == volume.beep_volume)
    {
        printf("开");
    }

    printf("\n");
    return;
}

static void autolink_deal_srs_freq(autolink_srs_st srs,
                                   void* userdata)
{
    printf("SRS频率:");
    switch(srs.srs_freq)
    {
        case SRS_FREQ_30:
            printf("30");
            break;
        case SRS_FREQ_60:
            printf("60");
            break;
        case SRS_FREQ_125:
            printf("125");
            break;
        case SRS_FREQ_250:
            printf("250");
            break;
        case SRS_FREQ_500:
            printf("500");
            break;
        case SRS_FREQ_1K:
            printf("1k");
            break;
        case SRS_FREQ_2K:
            printf("2K");
            break;
        case SRS_FREQ_4K:
            printf("4K");
            break;
        case SRS_FREQ_8K:
            printf("8K");
            break;
        case SRS_FREQ_16K:
            printf("16K");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf(" 值:%d",srs.srs_freq_value);

    printf("\n");
    return;
}


static void autolink_deal_gps_volume(autolink_volume_st volume,
                                     void* userdata)
{
    printf("GPS音量:%d\n",volume.gps_volume);
}

static void autolink_deal_camera_volume(autolink_volume_st volume,
                                        void* userdata)
{
    printf("倒车声音:");
    switch(volume.camera_volume)
    {
        case CAMERA_VOLUME_ON:
            printf("开");
            break;
        case CAMERA_VOLUME_OFF:
            printf("关");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}

static void autolink_deal_srs_state(autolink_srs_st srs,
                                    void* userdata)
{
    printf("SRS状态:");
    switch(srs.srs_state)
    {
        case SRS_STATE_ON:
            printf("开");
            break;
        case SRS_STATE_OFF:
            printf("关");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}

static void autolink_deal_srs_mode(autolink_srs_st srs,
                                   void* userdata)
{
    printf("SRS通道模式:");
    switch(srs.srs_mode)
    {
        case SRS_MODE_4P0:
            printf("4.0");
            break;
        case SRS_MODE_4P1:
            printf("4.1");
            break;
        case SRS_MODE_5P1:
            printf("5.1");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}

static void autolink_deal_headlight_state(autolink_headlight_state_em state,
                                          void* userdata)
{
    printf("大灯状态:");
    switch(state)
    {
        case HEADLIGHT_STATE_OFF:
            printf("关");
            break;
        case HEADLIGHT_STATE_ON:
            printf("开");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}


static void autolink_deal_superbass_state(autolink_superbass_state_em state,
                                          void* userdata)
{
    printf("重低音:");
    switch(state)
    {
        case SUPERBASS_STATE_OFF:
            printf("关");
            break;
        case SUPERBASS_STATE_ON:
            printf("开");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}


static void autolink_deal_brake_check(autolink_brake_check_em brake_check,
                                      void* userdata)
{
    printf("刹车检测:");
    switch(brake_check)
    {
        case BRAKE_CHECK_OFF:
            printf("关");
            break;
        case BRAKE_CHECK_ON:
            printf("开");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}


static void autolink_deal_brake_state(autolink_brake_state_em brake_state,
                                      void* userdata)
{
    printf("刹车状态:");
    switch(brake_state)
    {
        case BRAKE_STATE_OFF:
            printf("关");
            break;
        case BRAKE_STATE_ON:
            printf("开");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}


static void autolink_deal_gps_mixer(autolink_gps_mixer_em gps_mixer,
                                    void* userdata)
{
    printf("GPS混音:");
    switch(gps_mixer)
    {
        case GPS_MIXER_OFF:
            printf("关");
            break;
        case GPS_MIXER_ON:
            printf("开");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}

static void autolink_deal_gps_monitor(autolink_gps_monitor_em gps_monitor,
                                      void* userdata)
{
    printf("GPS监听:");
    switch(gps_monitor)
    {
        case GPS_MONITOR_OFF:
            printf("关");
            break;
        case GPS_MONITOR_ON:
            printf("开");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}

static void autolink_deal_bt_autoanswer(autolink_bt_st bt,
                                        void* userdata)
{
    printf("BT自动接听:");
    switch(bt.bt_autoanswer)
    {
        case BT_AUTOANSWER_OFF:
            printf("关");
            break;
        case BT_AUTOANSWER_ON:
            printf("开");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}

static void autolink_deal_bt_power(autolink_bt_st bt,
                                   void* userdata)
{
    printf("BT电源开关:");
    switch(bt.bt_power)
    {
        case BT_POWER_OFF:
            printf("关");
            break;
        case BT_POWER_ON:
            printf("开");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}

static void autolink_deal_bt_connect(autolink_bt_st bt,
                                     void* userdata)
{
    printf("BT自动连接:");
    switch(bt.bt_connect)
    {
        case BT_CONNECT_OFF:
            printf("关");
            break;
        case BT_CONNECT_ON:
            printf("开");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}

static void autolink_deal_radio_region(autolink_radio_st radio,
                                       void* userdata)
{
    printf("收音区域:");
    switch(radio.region)
    {
        case RADIO_REGION_EU:
            printf("欧洲");
            break;
        case RADIO_REGION_USA1:
            printf("USA1");
            break;
        case RADIO_REGION_USA2:
            printf("USA2");
            break;
        case RADIO_REGION_JP:
            printf("日本");
            break;
        case RADIO_REGION_RUS:
            printf("俄罗斯");
            break;
        case RADIO_REGION_AS:
            printf("亚洲");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}

static void autolink_deal_language(autolink_language_em language,
                                   void* userdata)
{
    printf("语言:");
    switch(language)
    {
        case LANGUAGE_ENGLISH:
            printf("英语");
            break;
        case LANGUAGE_SIMPLE_CN:
            printf("简体中文");
            break;
        case LANGUAGE_TRADITION_CN:
            printf("繁体中文");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}

static void autolink_deal_mcu_version(autolink_mcu_version mcu_version,
                                      void* userdata)
{
    printf("MCU版本号:%s\n",mcu_version);
}

static void autolink_deal_mcu_update_request(autolink_mcu_update_st mcu,void* userdata)
{
    printf("MCU升级:");
    switch(mcu.request)
    {
        case MCU_UPDATE_NONE:
            printf("不请求");
            break;
        case MCU_UPDATE_REQUEST:
            printf("请求");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}

static void autolink_deal_mcu_update_data(autolink_mcu_update_st mcu,void* userdata)
{
    printf("MCU升级第%d包数据\n",mcu.order);
}

static void autolink_deal_mcu_update_result(autolink_mcu_update_st mcu,void* userdata)
{
    printf("MCU升级结果:");
    switch(mcu.result)
    {
        case MCU_UPDATE_FAILED:
            printf("失败");
            break;
        case MCU_UPDATE_SUCCESS:
            printf("成功");
            break;
        default:
            printf("UNKOWN");
            break;
    }

    printf("\n");
}

static void autolink_mcu_state(autolink_mcu_info_type_em type,
                               autolink_mcu_info_data_st mcudata,
                               void* userdata)
{
    switch(type)
    {
        case TYPE_CAMERA:
            autolink_deal_camera(mcudata.camera_type,
                                 mcudata.camera_state,
                                 userdata);
            break;
        case TYPE_VALID_SOURCE:
            autolink_deal_valid_source(mcudata.source.valid_source,
                                       userdata);
            break;
        case TYPE_ACC:
            autolink_deal_acc(mcudata.acc_state,
                              userdata);
            break;
        case TYPE_INIT:
            autolink_deal_init(mcudata.init_complete,
                               userdata);
            break;
        case TYPE_WORK_UI_SOURCE:
            autolink_deal_work_ui_source(mcudata.source,
                                         userdata);
            break;
        case TYPE_SYSTEM_VOLUME:
            autolink_deal_system_volume(mcudata.volume.system_volume,
                                        mcudata.volume.system_volume_show,
                                        userdata);
            break;
        case TYPE_BTPHONE_VOLUME:
            autolink_deal_btphone_volume(mcudata.volume.btphone_volume,
                                         mcudata.volume.btphone_volume_sync,
                                         userdata);
            break;
        case TYPE_MUTE_VOLUME:
            autolink_deal_mute_volume(mcudata.volume.mute,userdata);
            break;
        case TYPE_TIME_VALUE:
            autolink_deal_time_value(mcudata.time,userdata);
            break;
        case TYPE_TIME_FORMAT:
            autolink_deal_time_format(mcudata.time,userdata);
            break;
        case TYPE_LCD_STATE:
            autolink_deal_lcd_state(mcudata.lcd.lcd_state,userdata);
            break;
        case TYPE_RADIO_MAINFREQ:
            autolink_deal_radio_mainfreq(mcudata.radio,userdata);
            break;
        case TYPE_RADIO_SAVEFREQ:
            autolink_deal_radio_savefreq(mcudata.radio,userdata);
            break;
        case TYPE_RADIO_ALL_SAVEFREQ:
            autolink_deal_radio_all_savefreq(mcudata.radio,userdata);
            break;
        case TYPE_EQ_STATE:
            autolink_deal_eq_state(mcudata.eq,userdata);
            break;
        case TYPE_EQ_MODE:
            autolink_deal_eq_mode(mcudata.eq,userdata);
            break;
        case TYPE_LCD_BRIGHTNESS:
            autolink_deal_lcd_brightness(mcudata.lcd,userdata);
            break;
        case TYPE_LCD_CONTRAST:
            autolink_deal_lcd_contrast(mcudata.lcd,userdata);
            break;
        case TYPE_LCD_HUE:
            autolink_deal_lcd_hue(mcudata.lcd,userdata);
            break;
        case TYPE_VIDEO_MODE:
            autolink_deal_video_mode(mcudata.video_mode,userdata);
            break;
        case TYPE_BEEP_VOLUME:
            autolink_deal_beep_volume(mcudata.volume,userdata);
            break;
        case TYPE_SRS_FREQ:
            autolink_deal_srs_freq(mcudata.srs,userdata);
            break;
        case TYPE_GPS_VOLUME:
            autolink_deal_gps_volume(mcudata.volume,userdata);
            break;
        case TYPE_CAMERA_VOLUME:
            autolink_deal_camera_volume(mcudata.volume,userdata);
            break;
        case TYPE_SRS_STATE:
            autolink_deal_srs_state(mcudata.srs,userdata);
            break;
        case TYPE_SRS_MODE:
            autolink_deal_srs_mode(mcudata.srs,userdata);
            break;
        case TYPE_HEADLIGHT_STATE:
            autolink_deal_headlight_state(mcudata.headlight_state,userdata);
            break;
        case TYPE_SUPERBASS_STATE:
            autolink_deal_superbass_state(mcudata.superbass_state,userdata);
            break;
        case TYPE_BRAKE_CHECK:
            autolink_deal_brake_check(mcudata.brake_check,userdata);
            break;
        case TYPE_BRAKE_STATE:
            autolink_deal_brake_state(mcudata.brake_state,userdata);
            break;
        case TYPE_GPS_MIXER:
            autolink_deal_gps_mixer(mcudata.gps_mixer,userdata);
            break;
        case TYPE_GPS_MONITOR:
            autolink_deal_gps_monitor(mcudata.gps_monitor,userdata);
            break;
        case TYPE_BT_AUTOANSWER:
            autolink_deal_bt_autoanswer(mcudata.bt,userdata);
            break;
        case TYPE_BT_POWER:
            autolink_deal_bt_power(mcudata.bt,userdata);
            break;
        case TYPE_BT_CONNECT:
            autolink_deal_bt_connect(mcudata.bt,userdata);
            break;
        case TYPE_RADIO_REGION:
            autolink_deal_radio_region(mcudata.radio,userdata);
            break;
        case TYPE_LANGUAGE:
            autolink_deal_language(mcudata.language,userdata);
            break;
        case TYPE_MCU_VERSION:
            autolink_deal_mcu_version(mcudata.mcu_version,userdata);
            break;
        case TYPE_MCU_UPDATE_REQUEST:
            autolink_deal_mcu_update_request(mcudata.mcu_update,userdata);
            break;
        case TYPE_MCU_UPDATE_DATA:
            autolink_deal_mcu_update_data(mcudata.mcu_update,userdata);
            break;
        case TYPE_MCU_UPDATE_RESULT:
            autolink_deal_mcu_update_result(mcudata.mcu_update,userdata);
            break;
        default:
            printf("UNKOWN TYPE\n");
            break;
}

    return ;
}


int main()
{
    autolink_mcu_init();

    autolink_reg_mcu_state(autolink_mcu_state,NULL);

    autolink_mcu_info_data_st mcu_data;

    int i = 0;
    int j = 0;
    int k = 0;

    #if 0
    mcu_data.source.work_ui_source_ui_previous = UI_SOURCE_SD;
    mcu_data.source.work_ui_user_state = USER_STATE_BACKSIGHT | USER_STATE_GPS;
    mcu_data.source.work_ui_source_ishome = UI_ISHOME_FALSE;
    for(i=UI_SOURCE_STUB;i<=UI_SOURCE_SYNC;i++)
    {
        mcu_data.source.work_ui_source_current = i;
        autolink_send_mcu_state(TYPE_WORK_UI_SOURCE,mcu_data);
        getchar();
    }

    mcu_data.source.work_ui_source_current = UI_SOURCE_SD;
    mcu_data.source.work_ui_user_state = USER_STATE_BACKSIGHT | USER_STATE_GPS;
    mcu_data.source.work_ui_source_ishome = UI_ISHOME_TRUE;
    for(i=UI_SOURCE_STUB;i<=UI_SOURCE_SYNC;i++)
    {
        mcu_data.source.work_ui_source_ui_previous = i;
        autolink_send_mcu_state(TYPE_WORK_UI_SOURCE,mcu_data);
        getchar();
    }

    mcu_data.source.work_ui_user_state = USER_STATE_NORMAL;
    autolink_send_mcu_state(TYPE_WORK_UI_SOURCE,mcu_data);
    getchar();
    mcu_data.source.work_ui_user_state = USER_STATE_SETUP;
    autolink_send_mcu_state(TYPE_WORK_UI_SOURCE,mcu_data);
    getchar();
    mcu_data.source.work_ui_user_state = USER_STATE_GPS;
    autolink_send_mcu_state(TYPE_WORK_UI_SOURCE,mcu_data);
    getchar();
    mcu_data.source.work_ui_user_state = USER_STATE_BACKSIGHT;
    autolink_send_mcu_state(TYPE_WORK_UI_SOURCE,mcu_data);
    getchar();
    mcu_data.source.work_ui_user_state = USER_STATE_PHOTO;
    autolink_send_mcu_state(TYPE_WORK_UI_SOURCE,mcu_data);
    getchar();
    mcu_data.source.work_ui_user_state = USER_STATE_MP3;
    autolink_send_mcu_state(TYPE_WORK_UI_SOURCE,mcu_data);
    getchar();
    mcu_data.source.work_ui_user_state = USER_STATE_MP4;
    autolink_send_mcu_state(TYPE_WORK_UI_SOURCE,mcu_data);
    getchar();
    mcu_data.source.work_ui_user_state = USER_STATE_BT;
    autolink_send_mcu_state(TYPE_WORK_UI_SOURCE,mcu_data);
    getchar();
    #endif


    #if 0
    for(i=AUDIO_SOURCE_STUB;i<=AUDIO_SOURCE_AUX;i++)
    {
        mcu_data.source.work_audio_source_current = i;
        autolink_send_mcu_state(TYPE_WORK_AUDIO_SOURCE,mcu_data);
        getchar();
    }
    #endif

    #if 0
    mcu_data.gps_sound = GPS_SOUND_START;
    mcu_data.notify_sound = NOTIFY_SOUND_START;
    autolink_send_mcu_state(TYPE_GPS_NOTIFY_SOUND,mcu_data);
    getchar();

    mcu_data.gps_sound = GPS_SOUND_END;
    mcu_data.notify_sound = NOTIFY_SOUND_END;
    autolink_send_mcu_state(TYPE_GPS_NOTIFY_SOUND,mcu_data);
    getchar();

    mcu_data.gps_sound = GPS_SOUND_START;
    mcu_data.notify_sound = NOTIFY_SOUND_END;
    autolink_send_mcu_state(TYPE_GPS_NOTIFY_SOUND,mcu_data);
    getchar();

    mcu_data.gps_sound = GPS_SOUND_END;
    mcu_data.notify_sound = NOTIFY_SOUND_START;
    autolink_send_mcu_state(TYPE_GPS_NOTIFY_SOUND,mcu_data);
    getchar();
    #endif

    #if 0
    mcu_data.bt.btphone_state = BTPHONE_END;
    autolink_send_mcu_state(TYPE_BTPHONE_STATE,mcu_data);

    mcu_data.bt.btphone_state = BTPHONE_START;
    autolink_send_mcu_state(TYPE_BTPHONE_STATE,mcu_data);
    #endif


    #if 0
    mcu_data.volume.system_volume = 20;
    mcu_data.volume.system_volume_show = VOLUME_BAR_SHOW_TRUE;
    autolink_send_mcu_state(TYPE_SYSTEM_VOLUME,mcu_data);

    mcu_data.volume.system_volume_show = VOLUME_BAR_SHOW_FALSE;
    autolink_send_mcu_state(TYPE_SYSTEM_VOLUME,mcu_data);
    #endif

    #if 0
    mcu_data.volume.btphone_volume = 20;
    mcu_data.volume.btphone_volume_sync = VOLUME_BAR_SYNC_TRUE;
    autolink_send_mcu_state(TYPE_BTPHONE_VOLUME,mcu_data);

    mcu_data.volume.btphone_volume = 32;
    mcu_data.volume.btphone_volume_sync = VOLUME_BAR_SYNC_FALSE;
    autolink_send_mcu_state(TYPE_BTPHONE_VOLUME,mcu_data);
    #endif

    #if 0
    mcu_data.volume.mute = VOLUME_MUTE_FALSE;
    autolink_send_mcu_state(TYPE_MUTE_VOLUME,mcu_data);

    mcu_data.volume.mute = VOLUME_MUTE_TRUE;
    autolink_send_mcu_state(TYPE_MUTE_VOLUME,mcu_data);
    #endif

    #if 0
    mcu_data.time.year     = 2016;
    mcu_data.time.mon      = 3;
    mcu_data.time.day      = 8;
    mcu_data.time.hour     = 18;
    mcu_data.time.min      =  0;
    mcu_data.time.sec      = 12;
    autolink_send_mcu_state(TYPE_TIME_VALUE,mcu_data);
    #endif

    #if 0
    mcu_data.time.time_format     = TIME_FORMAT_24H;
    autolink_send_mcu_state(TYPE_TIME_FORMAT,mcu_data);

    mcu_data.time.time_format     = TIME_FORMAT_12H;
    autolink_send_mcu_state(TYPE_TIME_FORMAT,mcu_data);
    #endif

    #if 0
    mcu_data.lcd.lcd_state     = LCD_STATE_ON;
    autolink_send_mcu_state(TYPE_LCD_STATE,mcu_data);

    mcu_data.lcd.lcd_state     = LCD_STATE_OFF;
    autolink_send_mcu_state(TYPE_LCD_STATE,mcu_data);
    #endif

    #if 0
    mcu_data.radio.set.band     = RADIO_BAND_AM;
    mcu_data.radio.set.freq_position     = 32;
    mcu_data.radio.set.freq     = 10000;
    mcu_data.radio.set_type     = RADIO_SET_SELECT;
    autolink_send_mcu_state(TYPE_RADIO_SET_FREQ,mcu_data);

    mcu_data.radio.set.band     = RADIO_BAND_FM;
    mcu_data.radio.set.freq_position     = 48;
    mcu_data.radio.set.freq     = 87.5;
    mcu_data.radio.set_type     = RADIO_SET_SAVE;
    autolink_send_mcu_state(TYPE_RADIO_SET_FREQ,mcu_data);

    mcu_data.radio.set.band     = RADIO_BAND_FM;
    mcu_data.radio.set.freq_position     = 49;
    mcu_data.radio.set.freq     = 85.5;
    mcu_data.radio.set_type     = RADIO_SET_SAVE;
    autolink_send_mcu_state(TYPE_RADIO_SET_FREQ,mcu_data);
    #endif

    #if 0
    for(i=EQ_STATE_BASS;i<=EQ_STATE_LR_BALANCE;i++)
    {
        mcu_data.eq.eq_state            = i;
        mcu_data.eq.eq_state_value      = 30+i;
        autolink_send_mcu_state(TYPE_EQ_STATE,mcu_data);
        getchar();
    }
    #endif

    #if 0
    for(i=EQ_MODE_USER;i<=EQ_MODE_PEACE;i++)
    {
        mcu_data.eq.eq_mode            = i;
        autolink_send_mcu_state(TYPE_EQ_MODE,mcu_data);
        getchar();
    }

    #endif

    #if 0
    mcu_data.lcd.brightness         = 80;
    autolink_send_mcu_state(TYPE_LCD_BRIGHTNESS,mcu_data);
    #endif

    #if 0
    mcu_data.lcd.contrast           = 70;
    autolink_send_mcu_state(TYPE_LCD_CONTRAST,mcu_data);
    #endif

    #if 0
    mcu_data.lcd.hue                = 60;
    autolink_send_mcu_state(TYPE_LCD_HUE,mcu_data);
    #endif

    #if 0
    for(i=VIDEO_MODE_STANDARD;i<=VIDEO_MODE_USER;i++)
    {
        mcu_data.video_mode            = i;
        autolink_send_mcu_state(TYPE_VIDEO_MODE,mcu_data);
        getchar();
    }
    #endif



    #if 0
    mcu_data.volume.beep_volume    = BEEP_VOLUME_ON;
    autolink_send_mcu_state(TYPE_BEEP_VOLUME,mcu_data);

    mcu_data.volume.beep_volume    = BEEP_VOLUME_OFF;
    autolink_send_mcu_state(TYPE_BEEP_VOLUME,mcu_data);
    getchar();
    #endif

    #if 0
    for(i=SRS_FREQ_30;i<=SRS_FREQ_16K;i++)
    {
        mcu_data.srs.srs_freq           = i;
        mcu_data.srs.srs_freq_value     = 30+i;
        autolink_send_mcu_state(TYPE_SRS_FREQ,mcu_data);
        getchar();
    }
    #endif

    #if 0
    mcu_data.volume.gps_volume      = 48;
    autolink_send_mcu_state(TYPE_GPS_VOLUME,mcu_data);
    #endif

    #if 0
    mcu_data.volume.camera_volume   = CAMERA_VOLUME_ON;
    autolink_send_mcu_state(TYPE_CAMERA_VOLUME,mcu_data);

    mcu_data.volume.camera_volume   = CAMERA_VOLUME_OFF;
    autolink_send_mcu_state(TYPE_CAMERA_VOLUME,mcu_data);
    #endif

    #if 0
    mcu_data.srs.srs_state   = SRS_STATE_ON;
    autolink_send_mcu_state(TYPE_SRS_STATE,mcu_data);

    mcu_data.srs.srs_state   = SRS_STATE_OFF;
    autolink_send_mcu_state(TYPE_SRS_STATE,mcu_data);
    #endif

    #if 0
    for(i=SRS_MODE_4P0;i<=SRS_MODE_5P1;i++)
    {
        mcu_data.srs.srs_mode   = i;
        autolink_send_mcu_state(TYPE_SRS_MODE,mcu_data);
        getchar();
    }
    #endif

    #if 0
    mcu_data.headlight_state   = HEADLIGHT_STATE_ON;
    autolink_send_mcu_state(TYPE_HEADLIGHT_STATE,mcu_data);

    mcu_data.headlight_state   = HEADLIGHT_STATE_OFF;
    autolink_send_mcu_state(TYPE_HEADLIGHT_STATE,mcu_data);
    #endif

    #if 0
    mcu_data.superbass_state   = SUPERBASS_STATE_ON;
    autolink_send_mcu_state(TYPE_SUPERBASS_STATE,mcu_data);

    mcu_data.superbass_state   = SUPERBASS_STATE_OFF;
    autolink_send_mcu_state(TYPE_SUPERBASS_STATE,mcu_data);
    #endif


    #if 0
    mcu_data.brake_check   = BRAKE_CHECK_ON;
    autolink_send_mcu_state(TYPE_BRAKE_CHECK,mcu_data);

    mcu_data.brake_check   = BRAKE_CHECK_OFF;
    autolink_send_mcu_state(TYPE_BRAKE_CHECK,mcu_data);
    getchar();
    #endif

    #if 0
    mcu_data.brake_state   = BRAKE_STATE_ON;
    autolink_send_mcu_state(TYPE_BRAKE_STATE,mcu_data);

    mcu_data.brake_state   = BRAKE_STATE_OFF;
    autolink_send_mcu_state(TYPE_BRAKE_STATE,mcu_data);
    getchar();
    #endif

    #if 0
    mcu_data.gps_mixer   = GPS_MIXER_ON;
    autolink_send_mcu_state(TYPE_GPS_MIXER,mcu_data);

    mcu_data.gps_mixer   = GPS_MIXER_OFF;
    autolink_send_mcu_state(TYPE_GPS_MIXER,mcu_data);
    getchar();
    #endif

    #if 0
    mcu_data.gps_monitor   = GPS_MONITOR_ON;
    autolink_send_mcu_state(TYPE_GPS_MONITOR,mcu_data);

    mcu_data.gps_monitor   = GPS_MONITOR_OFF;
    autolink_send_mcu_state(TYPE_GPS_MONITOR,mcu_data);
    getchar();
    #endif




    #if 0
    mcu_data.bt.bt_autoanswer   = BT_AUTOANSWER_ON;
    autolink_send_mcu_state(TYPE_BT_AUTOANSWER,mcu_data);

    mcu_data.bt.bt_autoanswer   = BT_AUTOANSWER_OFF;
    autolink_send_mcu_state(TYPE_BT_AUTOANSWER,mcu_data);
    getchar();
    #endif

    #if 0
    mcu_data.bt.bt_power   = BT_POWER_ON;
    autolink_send_mcu_state(TYPE_BT_POWER,mcu_data);

    mcu_data.bt.bt_power   = BT_POWER_OFF;
    autolink_send_mcu_state(TYPE_BT_POWER,mcu_data);
    getchar();
    #endif

    #if 0
    mcu_data.bt.bt_connect   = BT_CONNECT_ON;
    autolink_send_mcu_state(TYPE_BT_CONNECT,mcu_data);

    mcu_data.bt.bt_connect   = BT_CONNECT_OFF;
    autolink_send_mcu_state(TYPE_BT_CONNECT,mcu_data);
    getchar();
    #endif

    #if 0
    for(i=RADIO_REGION_EU;i<=RADIO_REGION_AS;i++)
    {
        mcu_data.radio.region  = i;
        autolink_send_mcu_state(TYPE_RADIO_REGION,mcu_data);
        getchar();
    }

    #endif

    #if 0
    for(i=LANGUAGE_ENGLISH;i<=LANGUAGE_TRADITION_CN;i++)
    {
        mcu_data.language  = i;
        autolink_send_mcu_state(TYPE_LANGUAGE,mcu_data);
        getchar();
    }
    #endif


    #if 0
    mcu_data.media.current_type_folder  = 1000;
    mcu_data.media.all_type_folder  = 2000;
    autolink_send_mcu_state(TYPE_MEDIA_FOLDERS,mcu_data);
    #endif

    #if 0
    mcu_data.media.current_type_file  = 3000;
    mcu_data.media.all_type_file  = 4000;
    autolink_send_mcu_state(TYPE_MEDIA_FILES,mcu_data);
    #endif

    #if 0
    for(i=MEDIA_TYPE_MP3;i<=MEDIA_TYPE_MP4;i++)
    {
        mcu_data.media.current_type  = i;
        autolink_send_mcu_state(TYPE_MEDIA_PLAYING_TYPE,mcu_data);
        getchar();
    }
    #endif

    #if 0
    mcu_data.media.current_hour     = 1;
    mcu_data.media.current_min      = 2;
    mcu_data.media.current_sec      = 29;
    autolink_send_mcu_state(TYPE_MEDIA_PLAYING_TIME,mcu_data);
    getchar();
    #endif

    #if 0
    for(i=MEDIA_READING;i<=MEDIA_STOP;i++)
    {
        mcu_data.media.state     = i;
        autolink_send_mcu_state(TYPE_MEDIA_PLAYING_STATE,mcu_data);
        getchar();
    }
    #endif

    #if 0
    mcu_data.media.rdm     = MEDIA_RDM_OFF;
    for(i=MEDIA_RPT_OFF;i<=MEDIA_RPT_AB;i++)
    {
        mcu_data.media.rpt     = i;
        autolink_send_mcu_state(TYPE_MEDIA_PLAYING_MODE,mcu_data);
        getchar();
    }


    for(i=MEDIA_RDM_OFF;i<=MEDIA_RDM_ON;i++)
    {
        mcu_data.media.rdm     = i;
        autolink_send_mcu_state(TYPE_MEDIA_PLAYING_MODE,mcu_data);
        getchar();
    }

    #endif

    #if 0
    strcpy(mcu_data.media.name,"123.mp3");
    autolink_send_mcu_state(TYPE_MEDIA_PLAYING_NAME,mcu_data);
    #endif



    #if 0
    mcu_data.mcu_update.request = MCU_UPDATE_REQUEST;
    autolink_send_mcu_state(TYPE_MCU_UPDATE_REQUEST,mcu_data);
    getchar();

    mcu_data.mcu_update.request = MCU_UPDATE_NONE;
    autolink_send_mcu_state(TYPE_MCU_UPDATE_REQUEST,mcu_data);
    getchar();
    #endif

    #if 0
    mcu_data.mcu_update.package = 1000;
    autolink_send_mcu_state(TYPE_MCU_UPDATE_PACKAGE,mcu_data);
    #endif

    #if 0
    mcu_data.mcu_update.order = 10000;
    //read update file, fill in mcu_data.mcu_update.data
    memcpy(mcu_data.mcu_update.data,"test",4);
    mcu_data.mcu_update.len = 4;
    autolink_send_mcu_state(TYPE_MCU_UPDATE_DATA,mcu_data);
    #endif

    #if 0
    autolink_send_mcu_state(TYPE_MCU_UPDATE_RESET,mcu_data);
    #endif



    while(1)
    {
        sleep(5);
    }
    return 0;
}
