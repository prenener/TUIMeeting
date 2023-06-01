/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module:   TUICommonDefine @ TUIKitEngine
 * Function: TUIKitEngine 复用型定义
 */
#import <Foundation/Foundation.h>
#import "TUIEngineSymbolExport.h"

/**
 * [TUIVideoView] 用于渲染视频画面的渲染控件
 * TUIKitEngine 中有很多需要操控视频画面的接口，这些接口都需要您指定视频渲染控件。
 */
#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
#import <UIKit/UIKit.h>
typedef UIView TUIVideoView;
typedef UIImage TUIImage;
typedef UIEdgeInsets TUIEdgeInsets;
#elif TARGET_OS_MAC
#import <AppKit/AppKit.h>
typedef NSView TUIVideoView;
typedef NSImage TUIImage;
typedef NSEdgeInsets TUIEdgeInsets;
#endif

/**
 * 1.1 错误码枚举定义
 */
typedef NS_ENUM(NSInteger, TUIError) {

    ///操作成功
    TUIErrorSuccess = 0,

    ///暂未归类的通用错误
    TUIErrorFailed = -1,

    ///请求被限频，请稍后重试
    TUIErrorFreqLimit = -2,

    ///未找到SDKAppID，请在腾讯云视立方SDK控制台确认应用信息: https://console.cloud.tencent.com/vcube/project/manage
    TUIErrorSDKAppIDNotFound = -1000,

    ///调用 API 时，传入的参数不合法，检查入参是否合法
    TUIErrorInvalidParameter = -1001,

    ///未登录,请调用Login接口
    TUIErrorSdkNotInitialized = -1002,

    ///获取权限失败，当前未授权音/视频权限，请查看是否开启设备权限。Room场景下请使用以下错误码来处理:
    ///摄像头没有系统授权: ERR_CAMERA_NOT_AUTHORIZED
    ///麦克风没有系统授权: ERR_MICROPHONE_NOT_AUTHORIZED
    TUIErrorPermissionDenied = -1003,

    ///该功能需要开通额外的套餐，请在腾讯云视立方SDK按需开通对应套餐: https://console.cloud.tencent.com/vcube/project/manage
    TUIErrorRequirePayment = -1004,

    ///系统问题，打开摄像头失败。检查摄像头设备是否正常
    TUIErrorCameraStartFail = -1100,

    ///摄像头没有系统授权, 检查系统授权
    TUIErrorCameraNotAuthorized = -1101,

    ///摄像头被占用，检查是否有其他进程使用摄像头
    TUIErrorCameraOccupied = -1102,

    ///当前无摄像头设备，请插入摄像头设备解决该问题
    TUIErrorCameraDeviceEmpty = -1103,

    ///系统问题，打开麦克风失败。检查麦克风设备是否正常
    TUIErrorMicrophoneStartFail = -1104,

    ///麦克风没有系统授权，检查系统授权
    TUIErrorMicrophoneNotAuthorized = -1105,

    ///麦克风被占用
    TUIErrorMicrophoneOccupied = -1106,

    ///当前无麦克风设备
    TUIErrorMicrophoneDeviceEmpty = -1107,

    ///获取屏幕分享源（屏幕和窗口）失败，检查屏幕录制权限
    TUIErrorGetScreenSharingTargetFailed = -1108,

    ///开启屏幕分享失败，检查房间内是否有人正在屏幕分享
    TUIErrorStartScreenSharingFailed = -1109,

    ///进房时房间不存在，或许已被解散
    TUIErrorRoomIdNotExist = -2100,

    ///需要进房后才可使用此功能
    TUIErrorOperationInvalidBeforeEnterRoom = -2101,

    ///房主不支持退房操作，Conference(会议)房间类型: 可以先转让房主，再退房。LivingRoom(直播)房间类型: 房主只能解散房间
    TUIErrorExitNotSupportedForRoomOwner = -2102,

    ///当前房间类型下不支持该操作
    TUIErrorOperationNotSupportedInCurrentRoomType = -2103,

    ///当前发言模式下不支持该操作
    TUIErrorOperationNotSupportedInCurrentSpeechMode = -2104,

    ///创建房间ID 非法，自定义 ID 必须为可打印 ASCII 字符（0x20-0x7e），最长48个字节
    TUIErrorRoomIdInvalid = -2105,

    ///房间ID 已被使用，请选择别的房间ID
    TUIErrorRoomIdOccupied = -2106,

    ///房间名称非法，名称最长30字节，字符编码必须是 UTF-8 ，如果包含中文
    TUIErrorRoomNameInvalid = -2107,

    ///当前用户已在别的房间内，需要先退房才能加入新的房间:
    ///单个roomEngine实例只支持用户进入一个房间，如果要进入不同的房间请先退房或者使用新的roomEngine实例。
    TUIErrorAlreadyInOtherRoom = -2108,

    ///用户不存在
    TUIErrorUserNotExist = -2200,

    ///用户不在当前房间内
    TUIErrorUserNotEntered = -2201,

    ///需要房主权限才能操作
    TUIErrorUserNeedOwnerPermission = -2300,

    ///需要房主或者管理员权限才能操作
    TUIErrorUserNeedAdminPermission = -2301,

    ///信令请求无权限，比如取消非自己发起的邀请。
    TUIErrorRequestNoPermission = -2310,

    ///信令请求ID 无效或已经被处理过。
    TUIErrorRequestIdInvalid = -2311,

    ///最大麦位超出套餐包数量限制
    TUIErrorMaxSeatCountLimit = -2340,

    ///当前用户已经在麦位上
    TUIErrorAlreadyInSeat = -2341,

    ///当前麦位已经有人了
    TUIErrorSeatOccupied = -2342,

    ///当前麦位被锁
    TUIErrorSeatLocked = -2343,

    ///麦位编号不存在
    TUIErrorSeatIndexNotExist = -2344,

    ///当前用户没有在麦上
    TUIErrorUserNotInSeat = -2345,

    ///上麦人数已满
    TUIErrorAllSeatOccupied = -2346,

    ///当前麦位音频被锁
    TUIErrorOpenMicrophoneNeedSeatUnlock = -2360,

    ///需要向房主或管理员申请后打开麦克风
    TUIErrorOpenMicrophoneNeedPermissionFromAdmin = -2361,

    ///当前麦位视频被锁, 需要由房主解锁麦位后，才能打开摄像头
    TUIErrorOpenCameraNeedSeatUnlock = -2370,

    ///需要向房主或管理员申请后打开摄像头
    TUIErrorOpenCameraNeedPermissionFromAdmin = -2371,

    ///当前房间已开启全员禁言
    TUIErrorSendMessageDisabledForAll = -2380,

    ///当前房间内，你已被已禁言
    TUIErrorSendMessageDisabledForCurrent = -2381,

};

/**
 * 1.2 网络质量
 */
typedef NS_ENUM(NSUInteger, TUINetworkQuality) {

    ///未定义
    TUINetworkQualityUnknown = 0,

    ///当前网络非常好
    TUINetworkQualityExcellent = 1,

    ///当前网络比较好
    TUINetworkQualityGood = 2,

    ///当前网络一般
    TUINetworkQualityPoor = 3,

    ///当前网络较差
    TUINetworkQualityBad = 4,

    ///当前网络很差
    TUINetworkQualityVeryBad = 5,

    ///当前网络不满足 TRTC 的最低要求
    TUINetworkQualityDown = 6,

};

/**
 * 1.3 网络质量信息
 */
TUIENGINE_EXPORT @interface TUINetworkInfo : NSObject

///用户ID
@property(nonatomic, copy, nullable) NSString* userId;

///网络质量
@property(nonatomic, assign) TUINetworkQuality quality;

///上行丢包率，单位 (%) 该数值越小越好
///如果 upLoss 为0%，则意味着上行链路的网络质量很好，上传到云端的数据包基本不发生丢失
///如果upLoss 为 30%，则意味着 SDK 向云端发送的音视频数据包中，会有 30%丢失在传输链路中
@property(nonatomic, assign) uint32_t upLoss;

///下行丢包率，单位 (%) 该数值越小越好
///如果downLoss 为0%，则意味着下行链路的网络质量很好，从云端接收的数据包基本不发生丢失
///如果downLoss 为 30%，则意味着云端向 SDK 传输的音视频数据包中，会有 30%丢失在传输链路中
@property(nonatomic, assign) uint32_t downLoss;

///网络延迟，单位 ms
@property(nonatomic, assign) uint32_t delay;

@end

/**
 * 1.4 消息
 */
TUIENGINE_EXPORT @interface TUIMessage : NSObject

///消息 ID
@property(nonatomic, strong, readonly, nonnull) NSString* messageId;

///消息文本
@property(nonatomic, strong, nonnull) NSString* message;

///消息时间
@property(nonatomic, assign) uint64_t timestamp;

///消息发送者
@property(nonatomic, strong, nonnull) NSString* userId;

///消息发送者昵称
@property(nonatomic, strong, nonnull) NSString* userName;

///消息发送者头像
@property(nonatomic, strong, nullable) NSString* avatarURL;

- (instancetype _Nonnull)initWithMessageId:(NSString* _Nonnull)messageId
                                   message:(NSString* _Nonnull)message
                                 timestamp:(uint64_t)timestamp
                                    userId:(NSString* _Nonnull)userId
                                  userName:(NSString* _Nonnull)userName
                                 avatarURL:(NSString* _Nullable)avatarURL;

@end

typedef void (^TUISuccessBlock)(void);
typedef void (^TUIErrorBlock)(TUIError code, NSString* _Nonnull message);
