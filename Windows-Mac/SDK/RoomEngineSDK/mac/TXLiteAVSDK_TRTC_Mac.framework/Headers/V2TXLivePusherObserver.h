/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module:   V2TXLivePusherObserver @ TXLiteAVSDK
 * Function: 腾讯云直播推流的回调通知
 * <H2>功能
 * 腾讯云直播的推流回调通知。
 * <H2>介绍
 * 可以接收 {@link V2TXLivePusher} 推流器的一些推流通知，包括推流器连接状态、音视频首帧回调、统计数据、警告和错误信息等。
 */
#import "V2TXLiveDef.h"

NS_ASSUME_NONNULL_BEGIN

@protocol V2TXLivePusherObserver <NSObject>

@optional

/////////////////////////////////////////////////////////////////////////////////
//
//                   直播推流器事件回调
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 直播推流器错误通知，推流器出现错误时，会回调该通知
 *
 * @param code      错误码 {@link V2TXLiveCode}。
 * @param msg       错误信息。
 * @param extraInfo 扩展信息。
 */
- (void)onError:(V2TXLiveCode)code message:(NSString *)msg extraInfo:(NSDictionary *)extraInfo;

/**
 * 直播推流器警告通知
 *
 * @param code      警告码 {@link V2TXLiveCode}。
 * @param msg       警告信息。
 * @param extraInfo 扩展信息。
 */
- (void)onWarning:(V2TXLiveCode)code message:(NSString *)msg extraInfo:(NSDictionary *)extraInfo;

/**
 * 首帧音频采集完成的回调通知
 */
- (void)onCaptureFirstAudioFrame;

/**
 * 首帧视频采集完成的回调通知
 */
- (void)onCaptureFirstVideoFrame;

/**
 * 麦克风采集音量值回调
 *
 * @param volume 音量大小。
 * @note  调用 {@link enableVolumeEvaluation} 开启采集音量大小提示之后，会收到这个回调通知。
 */
- (void)onMicrophoneVolumeUpdate:(NSInteger)volume;

/**
 * 推流器连接状态回调通知
 *
 * @param status    推流器连接状态 {@link V2TXLivePushStatus}。
 * @param msg       连接状态信息。
 * @param extraInfo 扩展信息。
 */
- (void)onPushStatusUpdate:(V2TXLivePushStatus)status message:(NSString *)msg extraInfo:(NSDictionary *)extraInfo;

/**
 * 直播推流器统计数据回调
 *
 * @param statistics 推流器统计数据 {@link V2TXLivePusherStatistics}
 */
- (void)onStatisticsUpdate:(V2TXLivePusherStatistics *)statistics;

/**
 * 截图回调
 *
 * @param image 已截取的视频画面。
 * @note 调用 {@link snapshot} 截图之后，会收到这个回调通知。
 */
- (void)onSnapshotComplete:(nullable TXImage *)image;

/**
 * 本地采集并经过音频模块前处理、音效处理和混 BGM 后的音频数据回调
 *
 * 当您设置完音频数据自定义回调之后，SDK 内部会把刚采集到并经过前处理、音效处理和混 BGM 之后的数据，在最终进行网络编码之前，以 PCM 格式的形式通过本接口回调给您。
 * - 此接口回调出的音频时间帧长固定为 0.02s，格式为 PCM 格式。
 * - 由时间帧长转化为字节帧长的公式为`采样率 × 时间帧长 × 声道数 × 采样点位宽`。
 * - 以 SDK 默认的音频录制格式 48000 采样率、单声道、16采样点位宽为例，字节帧长为`48000 × 0.02s × 1 × 16bit = 15360bit = 1920字节`。
 * @param frame PCM 格式的音频数据帧。
 * @note
 * 1. 请不要在此回调函数中做任何耗时操作，由于 SDK 每隔 20ms 就要处理一帧音频数据，如果您的处理时间超过 20ms，就会导致声音异常。
 * 2. 此接口回调出的音频数据是可读写的，也就是说您可以在回调函数中同步修改音频数据，但请保证处理耗时。
 */
- (void)onProcessAudioFrame:(V2TXLiveAudioFrame *)frame;

/**
 * 自定义视频处理回调
 *
 * @note 需要调用 {@link enableCustomVideoProcess} 开启自定义视频处理，才会收到这个回调通知。
 * 【情况一】美颜组件会产生新的纹理
 * 如果您使用的美颜组件会在处理图像的过程中产生一帧全新的纹理（用于承载处理后的图像），那请您在回调函数中将 dstFrame.textureId 设置为新纹理的 ID。
 * <pre>
 *   - (void) onProcessVideoFrame:(V2TXLiveVideoFrame * _Nonnull)srcFrame dstFrame:(V2TXLiveVideoFrame * _Nonnull)dstFrame
 *   {
 *       GLuint dstTextureId = renderItemWithTexture(srcFrame.textureId, srcFrame.width, srcFrame.height);
 *       dstFrame.textureId = dstTextureId;
 *       return 0;
 *   }
 * </pre>
 *
 * 【情况二】美颜组件并不自身产生新纹理
 * 如果您使用的第三方美颜模块并不生成新的纹理，而是需要您设置给该模块一个输入纹理和一个输出纹理，则可以考虑如下方案：
 * <pre>
 *   - (void) onProcessVideoFrame:(V2TXLiveVideoFrame * _Nonnull)srcFrame dstFrame:(V2TXLiveVideoFrame * _Nonnull)dstFrame
 *   {
 *       thirdparty_process(srcFrame.textureId, srcFrame.width, srcFrame.height, dstFrame.textureId);
 *       return 0;
 *   }
 * </pre>
 *
 * @param srcFrame 用于承载未处理的视频画面。
 * @param dstFrame 用于承载处理过的视频画面。
 */
- (void)onProcessVideoFrame:(V2TXLiveVideoFrame *_Nonnull)srcFrame dstFrame:(V2TXLiveVideoFrame *_Nonnull)dstFrame;

/**
 * SDK 内部的 OpenGL 环境的销毁通知
 */
- (void)onGLContextDestroyed;

/**
 * 设置云端的混流转码参数的回调，对应于 {@link setMixTranscodingConfig} 接口
 *
 * @param code 0表示成功，其余值表示失败。
 * @param msg 具体错误原因。
 */
- (void)onSetMixTranscodingConfig:(V2TXLiveCode)code message:(NSString *)msg;

/**
 * 当屏幕分享开始时，SDK 会通过此回调通知
 */
- (void)onScreenCaptureStarted;

/**
 * 当屏幕分享停止时，SDK 会通过此回调通知
 *
 * @param reason 停止原因
 *               - 0：表示用户主动停止。
 *               - 1：iOS 表示录屏被系统中断；Mac、Windows 表示屏幕分享窗口被关闭。
 *               - 2：Windows 表示屏幕分享的显示屏状态变更（如接口被拔出、投影模式变更等）；其他平台不抛出。
 */
- (void)onScreenCaptureStopped:(int)reason;

/**
 * 录制任务开始的事件回调
 * 开始录制任务时，SDK 会抛出该事件回调，用于通知您录制任务是否已经顺利启动。对应于 {@link startLocalRecording} 接口。
 *
 * @param code 状态码。
 *               - 0：录制任务启动成功。
 *               - -1：录制任务启动失败。
 *               - -2: 文件后缀名有误（比如不支持的录制格式）。
 * @param storagePath 录制的文件地址。
 */
- (void)onLocalRecordBegin:(NSInteger)errCode storagePath:(NSString *)storagePath;

/**
 * 录制任务正在进行中的进展事件回调
 * 当您调用 {@link startLocalRecording} 成功启动本地媒体录制任务后，SDK 变会按一定间隔抛出本事件回调，【默认】：不抛出本事件回调。
 * 您可以在 {@link startLocalRecording} 时，设定本事件回调的抛出间隔参数。
 *
 * @param durationMs   录制时长。
 * @param storagePath  录制的文件地址。
 */
- (void)onLocalRecording:(NSInteger)durationMs storagePath:(NSString *)storagePath;

/**
 * 录制任务已经结束的事件回调
 * 停止录制任务时，SDK 会抛出该事件回调，用于通知您录制任务的最终结果。对应于 {@link stopLocalRecording} 接口。
 *
 * @param code 状态码。
 *               -  0：结束录制任务成功。
 *               - -1：录制失败。
 *               - -2：切换分辨率或横竖屏导致录制结束。
 * @param storagePath 录制的文件地址。
 */
- (void)onLocalRecordComplete:(NSInteger)errCode storagePath:(NSString *)storagePath;

@end

NS_ASSUME_NONNULL_END
