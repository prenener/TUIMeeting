/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module:   TUIRoomEngine @ TUIKitEngine
 * Function: TUIRoomEngine 主功能接口
 * Version: <:Version:>
 */

#import <Foundation/Foundation.h>

#import "TUIRoomDefine.h"
#import "TUIRoomObserver.h"

NS_ASSUME_NONNULL_BEGIN
@class TRTCCloud;
@class TXDeviceManager;
@class TXBeautyManager;
@class TXAudioEffectManager;
@class TRTCVideoEncParam;
@class TRTCScreenCaptureSourceInfo;

TUIENGINE_EXPORT @interface TUIRoomEngine : NSObject

/**
 * 1.1 登录接口，您需要先初始化用户信息后才能进入房间，并进行一系列的操作
 *
 * @param sdkAppId 它是腾讯云用于区分客户的唯一标识，进入腾讯云实时音视频 [控制台](https://console.cloud.tencent.com/rav)创建应用，即可看到SDKAppId
 * @param userId 用户ID，用于区分不同用户
 * @param userSig 用户签名，用于腾讯云流量的认证
 * @param onSuccess 成功回调
 * @param onError 失败回调
 */
+ (void)loginWithSDKAppId:(NSInteger)sdkAppId userId:(NSString *)userId userSig:(NSString *)userSig onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(login(sdkAppId:userId:userSig:onSuccess:onError:));

/**
 * 1.2 退出登录接口，会有主动离开房间操作、销毁资源
 *
 * @param onSuccess 成功回调
 * @param onError 失败回调
 */
+ (void)logout:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(logout(onSuccess:onError:));

/**
 * 1.3 设置本地用户名称和头像
 *
 * @param userName 用户名称
 * @param avatarURL 用户头像URL地址
 * @param onSuccess 成功回调
 * @param onError 失败回调
 */
+ (void)setSelfInfoWithUserName:(NSString *)userName avatarUrl:(NSString *)avatarURL onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(setSelfInfo(userName:avatarUrl:onSuccess:onError:));

/**
 * 1.4 获取本地用户登录的基本信息
 *
 * @return {@link TUILoginUserInfo} 用户登录信息
 */
+ (TUILoginUserInfo *)getSelfInfo NS_SWIFT_NAME(getSelfInfo());

/**
 * 1.5 设置本地用户信息
 *
 * @param userInfo 本地用户信息
 * @param onSuccess 成功回调
 * @param onError 失败回调
 */
+ (void)setSelfInfo:(TUILoginUserInfo *)userInfo onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(setSelfInfo(userInfo:onSuccess:onError:));

/**
 * 1.6 设置事件回调
 *
 * 您可以通过 TUIRoomObserver 获得各类事件通知（比如：错误码，远端用户进房，音视频状态参数等）
 * @param observer 监听的实例
 */
- (void)addObserver:(id<TUIRoomObserver>)observer NS_SWIFT_NAME(addObserver(_:));

/**
 * 1.7 移除事件回调
 *
 * @param observer 待移除的监听回调实例
 */
- (void)removeObserver:(id<TUIRoomObserver>)observer NS_SWIFT_NAME(removeObserver(_:));

/////////////////////////////////////////////////////////////////////////////////
//
//                   房间相关主动接口
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 2.1 创建房间
 *
 * @param roomInfo 房间信息，可以初始化房间的一些设置
 * @param onSuccess 成功回调
 * @param onError 失败回调
 */
- (void)createRoom:(TUIRoomInfo *)roomInfo onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(createRoom(_:onSuccess:onError:));

/**
 * 2.2 解散房间
 *
 * @param onSuccess 成功回调
 * @param onError 失败回调
 */
- (void)destroyRoom:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(destroyRoom(onSuccess:onError:));

/**
 * 2.3 进入房间
 *
 * @param roomId 房间ID
 * @param onSuccess 成功回调
 * @param onError 失败回调
 */
- (void)enterRoom:(NSString *)roomId onSuccess:(TUIRoomInfoBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(enterRoom(_:onSuccess:onError:));

/**
 * 2.4 离开房间
 *
 * @param syncWaiting 是否同步等待接口返回
 * @param onSuccess 成功回调
 * @param onError 失败回调
 */
- (void)exitRoom:(BOOL)syncWaiting onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(exitRoom(syncWaiting:onSuccess:onError:));

/**
 * 2.5 连接其他房间
 *
 * @note 用于直播场景下的申请跨房连麦
 * @param roomId 房间ID
 * @param userId 用户ID
 * @param timeout 超时时间，单位秒，如果设置为 0，SDK 不会做超时检测，也不会触发超时回调
 * @param onAccepted 邀请被接受的回调
 * @param onRejected 邀请被拒绝的回调
 * @param onCancelled 邀请被取消的回调
 * @param onTimeout 邀请超时未处理的回调
 * @param onError 邀请发生错误的回调
 * @return 请求体
 */
- (TUIRequest *)connectOtherRoom:(NSString *)roomId
                          userId:(NSString *)userId
                         timeout:(NSTimeInterval)timeout
                      onAccepted:(TUIRequestAcceptedBlock)onAccepted
                      onRejected:(TUIRequestRejectedBlock)onRejected
                     onCancelled:(TUIRequestCancelledBlock)onCancelled
                       onTimeout:(TUIRequestTimeoutBlock)onTimeout
                         onError:(TUIRequestErrorBlock)onError NS_SWIFT_NAME(connectOtherRoom(_:userId:timeout:onAccepted:onRejected:onCancelled:onTimeout:onError:));

/**
 * 2.6 断开与其他房间的连接
 *
 * @note 用于直播场景下的断开跨房连麦
 * @param onSuccess 成功回调
 * @param onError 失败回调
 */
- (void)disconnectOtherRoom:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(disconnectOtherRoom(onSuccess:onError:));

/**
 * 2.7 获取房间信息
 *
 * @param onSuccess 成功获取到房间信息回调，回调会包含 TUIRoomInfo 房间信息
 * @param onError 失败回调
 */
- (void)fetchRoomInfo:(TUIRoomInfoBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(fetchRoomInfo(onSuccess:onError:));

/**
 * 2.8 更新房间名称（只有管理员或房主能够调用）
 *
 * @param roomName 房间名称
 * @param onSuccess 成功回调
 * @param onError 失败回调
 */
- (void)updateRoomNameByAdmin:(NSString *)roomName onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(updateRoomNameByAdmin(roomName:onSuccess:onError:));

/**
 * 2.9  设置房间麦控模式（只有管理员或房主能够调用）
 *
 * @param mode kFreeToSpeak: 自由发言模式, 用户可以自由开启麦克风和扬声器;
 *             kApplyToSpeak: 申请发言模式，用户requestOpenLocalMicrophone 或 requestOpenLocalCamera 向房主或管理员申请后，方可打开麦克风和摄像头开始发言
 *             kkSpeakAfterTakingSeat: 上麦发言模式，KConference房间内，所有人在发言前，必须takeSeat，才能进行麦克风和摄像头操作。
 * @param onSuccess 成功回调
 * @param onError 错误回调
 */
- (void)updateRoomSpeechModeByAdmin:(TUISpeechMode)mode onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(updateRoomSpeechModeByAdmin(_:onSuccess:onError:));

/////////////////////////////////////////////////////////////////////////////////
//
//                   本地用户视图渲染、视频管理
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 3.1 设置本地用户视频渲染的视图控件
 *
 * @param streamType 视频流的类型，定义可参考 {@link TUIVideoStreamType} 的定义
 * @param view 视频渲染视图
 */
- (void)setLocalVideoView:(TUIVideoStreamType)streamType view:(TUIVideoView *__nullable)view NS_SWIFT_NAME(setLocalVideoView(streamType:view:));

/**
 * 3.2 打开本地摄像头
 *
 * @param isFront {@link YES}: 前置 {@link NO}: 后置
 * @param onSuccess 成功回调
 * @param onError 失败回调
 */
- (void)openLocalCamera:(BOOL)isFront quality:(TUIVideoQuality)quality onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(openLocalCamera(isFront:quality:onSuccess:onError:));

/**
 * 3.3 关闭本地摄像头
 */
- (void)closeLocalCamera NS_SWIFT_NAME(closeLocalCamera());

/**
 * 3.4 更新本地视频编码质量设置
 */
- (void)updateVideoQuality:(TUIVideoQuality)quality NS_SWIFT_NAME(updateVideoQuality(_:));

#if TARGET_OS_IPHONE

/**
 * 3.5 开始屏幕分享（该接口仅支持移动端）
 */
- (void)startScreenCaptureByReplaykit:(NSString *)appGroup NS_SWIFT_NAME(startScreenCapture(appGroup:))API_AVAILABLE(ios(11.0));

#endif

#if !TARGET_OS_IPHONE && TARGET_OS_MAC

/**
 * 3.8 开始屏幕分享（该接口仅支持桌面端 Mac OS 系统）
 *
 * @note 该接口可以抓取整个 Mac OS 系统的屏幕内容，或抓取您指定的某个应用的窗口内容，并将其分享给同房间中的其他用户。
 * @param view 渲染控件所在的父控件，可以设置为空值，表示不显示屏幕分享的预览效果。
 * @param onSuccess 成功回调
 * @param onError 错误回调
 */
- (void)startScreenCapture:(TUIVideoView *)view onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(startScreenCapture(view:onSuccess:onError:));

#endif

/**
 * 3.9  结束屏幕分享
 */
- (void)stopScreenCapture NS_SWIFT_NAME(stopScreenCapture());

#if !TARGET_OS_IPHONE && TARGET_OS_MAC

/**
 * 3.10 枚举可分享的屏幕和窗口（该接口仅支持 Mac OS 系统）
 *
 * 当您在对接桌面端系统的屏幕分享功能时，一般都需要展示一个选择分享目标的界面，这样用户能够使用这个界面选择是分享整个屏幕还是某个窗口通过本接口，您就可以查询到当前系统中可用于分享的窗口的 ID、名称以及缩略图
 * @return 窗口列表包括屏幕
 * @note 返回的列表中包含屏幕和应用窗口，屏幕是列表中的第一个元素, 如果用户有多个显示器，那么每个显示器都是一个分享目标
 */
- (NSArray<TUIShareTarget *> *)getScreenCaptureSources NS_SWIFT_NAME(getScreenCaptureSources());

/**
 * 3.11 选取要分享的屏幕或窗口（该接口仅支持 Mac OS 系统）
 *
 * 当您通过 getScreenCaptureSources 获取到可以分享的屏幕和窗口之后，您可以调用该接口选定期望分享的目标屏幕或目标窗口
 * 在屏幕分享的过程中，您也可以随时调用该接口以切换分享目标
 * @param targetId 指定分享源
 */
- (void)selectScreenCaptureTarget:(NSString *)targetId NS_SWIFT_NAME(selectScreenCaptureTarget(_:));

#endif

/**
 * 3.13 开始推送本地视频。默认开启
 */
- (void)startPushLocalVideo NS_SWIFT_NAME(startPushLocalVideo());

/**
 * 3.14 停止推送本地视频
 */
- (void)stopPushLocalVideo NS_SWIFT_NAME(stopPushLocalVideo());

/////////////////////////////////////////////////////////////////////////////////
//
//                   本地用户音频管理
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 4.1 打开本地麦克风
 *
 * @param quality 音频质量
 * @param onSuccess 成功回调
 * @param onError 失败回调
 */
- (void)openLocalMicrophone:(TUIAudioQuality)quality onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(openLocalMicrophone(_:onSuccess:onError:));

/**
 * 4.2 关闭本地麦克风
 */
- (void)closeLocalMicrophone NS_SWIFT_NAME(closeLocalMicrophone());

/**
 * 4.3 更新本地音频编码质量设置
 */
- (void)updateAudioQuality:(TUIAudioQuality)quality NS_SWIFT_NAME(updateAudioQuality(_:));

/**
 * 4.4 开始推送本地音频
 */
- (void)startPushLocalAudio NS_SWIFT_NAME(startPushLocalAudio());

/**
 * 4.5 停止推送本地音频
 */
- (void)stopPushLocalAudio NS_SWIFT_NAME(stopPushLocalAudio());

/////////////////////////////////////////////////////////////////////////////////
//
//                   远端用户视图渲染、视频管理
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 5.1 设置远端用户视频渲染的视图控件
 *
 * @param userId 远端用户ID
 * @param streamType 视频流的类型，定义可参考 {@link TUIVideoStreamType} 的定义
 * @param view 视频渲染视图
 */
- (void)setRemoteVideoView:(NSString *)userId streamType:(TUIVideoStreamType)streamType view:(TUIVideoView *__nullable)view NS_SWIFT_NAME(setRemoteVideoView(userId:streamType:view:));

/**
 * 5.2 开始播放远端用户视频
 *
 * @param userId 用户ID
 * @param streamType 视频流的类型 详细定义可以参考 {@link TUIVideoStreamType} 的定义
 * @param onPlaying 播放回调
 * @param onLoading 加载回调
 * @param onError 错误回调
 */
- (void)startPlayRemoteVideo:(NSString *)userId
                  streamType:(TUIVideoStreamType)streamType
                   onPlaying:(TUIPlayOnPlayingBlock)onPlaying
                   onLoading:(TUIPlayOnLoadingBlock)onLoading
                     onError:(TUIPlayOnErrorBlock)onError NS_SWIFT_NAME(startPlayRemoteVideo(userId:streamType:onPlaying:onLoading:onError:));

/**
 * 5.3 停止播放远端用户视频
 *
 * @param userId 用户ID
 * @param streamType 视频流的类型 详细定义可以参考 {@link TUIVideoStreamType} 的定义
 */
- (void)stopPlayRemoteVideo:(NSString *)userId streamType:(TUIVideoStreamType)streamType NS_SWIFT_NAME(stopPlayRemoteVideo(userId:streamType:));

/**
 * 5.4 将远端用户禁音
 *
 * @param userId 用户ID
 * @param isMute 是否禁音
 */
- (void)muteRemoteAudioStream:(NSString *)userId isMute:(BOOL)isMute;

/////////////////////////////////////////////////////////////////////////////////
//
//                   房间内用户信息
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 6.1  获取房间内的成员列表
 *
 * @param nextSequence 分页拉取标志，第一次拉取填0，回调成功 如果callback返回的数据中 nextSequence 不为零，需要分页，传入再次拉取，直至为0
 * @param onSuccess 成功回调，回调中包含 {@link TUIUserInfo} 数组
 * @param onError 错误回调
 */
- (void)getUserList:(NSInteger)nextSequence onSuccess:(TUIUserListResponseBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(getUserList(nextSequence:onSuccess:onError:));

/**
 * 6.2  获取成员信息
 *
 * @param userId 用户ID
 * @param onSuccess 成功回调，回调中包含 {@link TUIUserInfo} 数组
 * @param onError 错误回调
 */
- (void)getUserInfo:(NSString *)userId onSuccess:(TUIUserInfoBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(getUserInfo(_:onSuccess:onError:));

/////////////////////////////////////////////////////////////////////////////////
//
//                   房间内用户管理
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 7.1  修改用户角色（只有管理员或房主能够调用）
 *
 * @param userId 用户ID
 * @param role 用户角色 详细定义可以参考 {@link TUIRole} 的定义
 * @param onSuccess 成功回调
 * @param onError 错误回调
 */
- (void)changeUserRole:(NSString *)userId role:(TUIRole)role onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(changeUserRole(userId:role:onSuccess:onError:));

/**
 * 7.2  将远端用户踢出房间（只有管理员或房主能够调用）
 *
 * @param userId 用户ID
 * @param onSuccess 成功回调
 * @param onError 错误回调
 */
- (void)kickRemoteUserOutOfRoom:(NSString *)userId onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(kickRemoteUserOutOfRoom(_:onSuccess:onError:));

/////////////////////////////////////////////////////////////////////////////////
//
//                   房间内用户发言管理
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 8.1 控制当前房间内所有用户是否可打开音频流、视频流采集设备的权限状态，例如：全员禁止打开麦克风、全员禁止打开摄像头、全员禁止打开屏幕分享（目前仅会议场景下可用，并且只有管理员或房主能够调用）
 *
 * @param device 设备. 详细定义参考:{@link TUIMediaDevice}
 * @param isDisable 否禁用
 * @param onSuccess 操作成功回调
 * @param onError 操作失败回调
 */
- (void)disableDeviceForAllUserByAdmin:(TUIMediaDevice)device isDisable:(BOOL)isDisable onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(disableDeviceForAllUserByAdmin(device:isDisable:onSuccess:onError:));

/**
 * 8.2  请求远端用户打开媒体设备（只有管理员或房主能够调用）
 *
 * @param userId 用户ID
 * @param device 媒体设备。详细定义参考:{@link TUIMediaDevice}
 * @param timeout 超时时间，单位秒，如果设置为 0，SDK 不会做超时检测，也不会触发超时回调
 * @param onAccepted 邀请被接受的回调
 * @param onRejected 邀请被拒绝的回调
 * @param onCancelled 邀请被取消的回调
 * @param onTimeout 邀请超时未处理的回调
 * @param onError 邀请发生错误的回调
 * @return TUIRequest 请求体
 */
- (TUIRequest *)openRemoteDeviceByAdmin:(NSString *)userId
                                 device:(TUIMediaDevice)device
                                timeout:(NSTimeInterval)timeout
                             onAccepted:(nullable TUIRequestAcceptedBlock)onAccepted
                             onRejected:(nullable TUIRequestRejectedBlock)onRejected
                            onCancelled:(nullable TUIRequestCancelledBlock)onCancelled
                              onTimeout:(nullable TUIRequestTimeoutBlock)onTimeout
                                onError:(nullable TUIRequestErrorBlock)onError NS_SWIFT_NAME(openRemoteDeviceByAdmin(userId:device:timeout:onAccepted:onRejected:onCancelled:onTimeout:onError:));

/**
 * 8.3 关闭远端用户媒体设备（只有管理员或房主能够调用）
 *
 * @param userId 用户ID
 * @param device 媒体设备。详细定义参考:{@link TUIMediaDevice}
 * @param onSuccess 调用成功回调
 * @param onError 调用失败回调
 */
- (void)closeRemoteDeviceByAdmin:(NSString *)userId device:(TUIMediaDevice)device onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(closeRemoteDeviceByAdmin(userId:device:onSuccess:onError:));

/**
 * 8.4 请求打开本地媒体设备（普通用户可用）
 *
 * @param device 用户ID@param device 媒体设备。详细定义参考:{@link TUIMediaDevice}
 * @param timeout 超时时间，单位秒，如果设置为 0，SDK 不会做超时检测，也不会触发超时回调
 * @param onAccepted 邀请被接受的回调
 * @param onRejected 邀请被拒绝的回调
 * @param onCancelled 邀请被取消的回调
 * @param onTimeout 邀请超时未处理的回调
 * @param onError 邀请发生错误的回调
 * @return TUIRequest 请求体
 */
- (TUIRequest *)applyToAdminToOpenLocalDevice:(TUIMediaDevice)device
                                      timeout:(NSTimeInterval)timeout
                                   onAccepted:(nullable TUIRequestAcceptedBlock)onAccepted
                                   onRejected:(nullable TUIRequestRejectedBlock)onRejected
                                  onCancelled:(nullable TUIRequestCancelledBlock)onCancelled
                                    onTimeout:(nullable TUIRequestTimeoutBlock)onTimeout
                                      onError:(nullable TUIRequestErrorBlock)onError NS_SWIFT_NAME(applyToAdminToOpenLocalDevice(device:timeout:onAccepted:onRejected:onCancelled:onTimeout:onError:));

/////////////////////////////////////////////////////////////////////////////////
//
//                    房间内麦位管理
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 9.1  设置最大麦位数（仅支持进房前和创建房间时设置）
 *
 * @param maxSeatCount 最大麦位数
 * @param onSuccess 成功回调
 * @param onError 错误回调
 */
- (void)setMaxSeatCount:(NSUInteger)maxSeatCount onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(setMaxSeatCount(maxSeatCount:onSuccess:onError:));

/**
 * 9.2  获取麦位列表
 *
 * @param onSuccess 成功回调
 * @param onError 错误回调
 */
- (void)getSeatList:(TUISeatListResponseBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(getSeatList(onSuccess:onError:));

/**
 * 9.3  锁定麦位（只有管理员或房主能够调用，包括位置锁定、音频状态锁定和视频状态锁定）
 *
 * @param seatIndex 麦位编号
 * @param lockParams 锁麦参数。详情参考:{@link $TUISeatLockParam$}
 * @param onSuccess 成功回调
 * @param onError 错误回调
 */
- (void)lockSeatByAdmin:(NSInteger)seatIndex lockMode:(TUISeatLockParams *)lockParams onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(lockSeatByAdmin(_:lockMode:onSuccess:onError:));

/**
 * 9.4  上麦（上麦发言模式下，需要申请）
 *
 * @note 开启上麦发言模式时，需要向主持人或管理员发起申请才允许上麦。
 *       开启自由发言模式，直播场景可以自由上麦，上麦后开麦发言，会议场景无需调用该接口，即可开麦发言。
 * @param seatIndex 麦位编号。会议场景下无需关心该参数，填0即可。
 * @param timeout 超时时间，单位秒，如果设置为 0，SDK 不会做超时检测，也不会触发超时回调
 * @param onAccepted 邀请被接受的回调
 * @param onRejected 邀请被拒绝的回调
 * @param onCancelled 邀请被取消的回调
 * @param onTimeout 邀请超时未处理的回调
 * @param onError 邀请发生错误的回调
 * @return TUIRequest 请求体
 */
- (TUIRequest *)takeSeat:(NSInteger)seatIndex
                 timeout:(NSTimeInterval)timeout
              onAccepted:(TUIRequestAcceptedBlock)onAccepted
              onRejected:(TUIRequestRejectedBlock)onRejected
             onCancelled:(TUIRequestCancelledBlock)onCancelled
               onTimeout:(TUIRequestTimeoutBlock)onTimeout
                 onError:(TUIRequestErrorBlock)onError NS_SWIFT_NAME(takeSeat(_:timeout:onAccepted:onRejected:onCancelled:onTimeout:onError:));

/**
 * 9.5  下麦
 *
 * @param onSuccess 成功回调
 * @param onError 错误回调
 */
- (void)leaveSeat:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(leaveSeat(onSuccess:onError:));

/**
 * 9.6  主持人/管理员 邀请用户上麦
 *
 * @param seatIndex 麦位编号。会议场景无需关心，填0即可。
 * @param userId 用户ID
 * @param timeout 超时时间，单位秒，如果设置为 0，SDK 不会做超时检测，也不会触发超时回调
 * @param onAccepted 邀请被接受的回调
 * @param onRejected 邀请被拒绝的回调
 * @param onCancelled 邀请被取消的回调
 * @param onTimeout 邀请超时未处理的回调
 * @param onError 邀请发生错误的回调
 * @return TUIRequest 请求体
 */
- (TUIRequest *)takeUserOnSeatByAdmin:(NSInteger)seatIndex
                               userId:(NSString *)userId
                              timeout:(NSTimeInterval)timeout
                           onAccepted:(TUIRequestAcceptedBlock)onAccepted
                           onRejected:(TUIRequestRejectedBlock)onRejected
                          onCancelled:(TUIRequestCancelledBlock)onCancelled
                            onTimeout:(TUIRequestTimeoutBlock)onTimeout
                              onError:(TUIRequestErrorBlock)onError NS_SWIFT_NAME(takeUserOnSeatByAdmin(_:userId:timeout:onAccepted:onRejected:onCancelled:onTimeout:onError:));

/**
 * 9.7  主持人/管理员 将用户踢下麦
 *
 * @param seatIndex 麦位编号。会议场景无需关心，填0即可。
 * @param userId 用户ID
 * @param onSuccess 成功回调
 * @param onError 失败回调
 */
- (void)kickUserOffSeatByAdmin:(NSInteger)seatIndex userId:(NSString *)userId onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(kickUserOffSeatByAdmin(_:userId:onSuccess:onError:));

/////////////////////////////////////////////////////////////////////////////////
//
//                   文本消息
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 10.1  发送本文消息
 *
 * @param message 消息内容
 * @param onSuccess 成功回调
 * @param onError 错误回调
 */
- (void)sendTextMessage:(NSString *)message onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(sendTextMessage(_:onSuccess:onError:));

/**
 * 10.2  发送自定义消息
 *
 * @param message 消息内容
 * @param onSuccess 成功回调
 * @param onError 错误回调
 */
- (void)sendCustomMessage:(NSString *)message onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(sendCustomMessage(_:onSuccess:onError:));

/**
 * 10.3  禁用远端用户的发送文本消息能力（只有管理员或房主能够调用）
 *
 * @param userId 用户ID
 * @param isDisable 是否禁用
 * @param onSuccess 成功回调
 * @param onError 错误回调
 */
- (void)disableSendingMessageByAdmin:(NSString *)userId isDisable:(BOOL)isDisable onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(disableSendingMessageByAdmin(userId:isDisable:onSuccess:onError:));

/**
 * 10.4  禁用所有用户的发送文本消息能力（只有管理员或房主能够调用）
 *
 * @param isDisable 是否禁用
 * @param onSuccess 成功回调
 * @param onError 错误回调
 */
- (void)disableSendingMessageForAllUser:(BOOL)isDisable onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(disableSendingMessageByAdmin(_:onSuccess:onError:));

/////////////////////////////////////////////////////////////////////////////////
//
//                    信令管理
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 7.1  取消请求
 *
 * @note 可以使用此接口来取消已发出的请求
 * @param requestId 请求ID(发送请求的接口返回或者OnRequestReceived事件通知)
 * @param onSuccess 成功回调
 * @param onError 失败回调
 */
- (void)cancelRequest:(NSString *)requestId onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(cancelRequest(_:onSuccess:onError:));

/**
 * 7.2  回复请求
 *
 * @note 在收到信令请求时，可以使用此接口来回复接收到的请求
 * @param requestId 请求ID(发送请求的接口返回或者OnRequestReceived事件通知)
 * @param agree 是否同意 YES: 同意请求, NO: 拒绝请求
 * @param onSuccess 成功回调
 * @param onError 失败回调
 */
- (void)responseRemoteRequest:(NSString *)requestId agree:(BOOL)agree onSuccess:(TUISuccessBlock)onSuccess onError:(TUIErrorBlock)onError NS_SWIFT_NAME(responseRemoteRequest(_:agree:onSuccess:onError:));

/////////////////////////////////////////////////////////////////////////////////
//
//                    高级功能：获取TRTC实例
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 9.1 获得TRTC实例对象
 *
 * @return 返回TRTCCloud对象
 */
- (TRTCCloud *)getTRTCCloud NS_SWIFT_NAME(getTRTCCloud());

/**
 * 9.2 获得设备管理对象
 *
 * @return 返回TXDeviceManager对象
 */
- (TXDeviceManager *)getDeviceManager NS_SWIFT_NAME(getDeviceManager());

/**
 * 9.3 获得音效管理对象
 *
 * @return  返回TXAudioEffectManager对象
 */
- (TXAudioEffectManager *)getAudioEffectManager NS_SWIFT_NAME(getAudioEffectManager());

/**
 * 9.4 获得美颜管理对象
 *
 * @return  返回TXBeautyManager对象
 */
- (TXBeautyManager *)getBeautyManager NS_SWIFT_NAME(getBeautyManager());

@end
NS_ASSUME_NONNULL_END
