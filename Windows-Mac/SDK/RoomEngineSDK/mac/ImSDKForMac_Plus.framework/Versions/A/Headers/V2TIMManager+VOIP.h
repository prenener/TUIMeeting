/////////////////////////////////////////////////////////////////////
//
//                     腾讯云通信服务 IMSDK
//
//  模块名称：V2TIMManager+VOIP
//
//  消息 VoIP 推送接口
//
/////////////////////////////////////////////////////////////////////

#import "V2TIMManager.h"

NS_ASSUME_NONNULL_BEGIN

@class V2TIMVOIPConfig;

V2TIM_EXPORT @interface V2TIMManager (VOIP)

/**
 *  1.1 设置 VoIP 推送
 */
- (void)setVOIP:(V2TIMVOIPConfig *)config succ:(V2TIMSucc __nullable)succ fail:(V2TIMFail __nullable)fail;

@end


V2TIM_EXPORT @interface V2TIMVOIPConfig : NSObject

/**
 * VoIP device token
 */
@property (nonatomic, strong, nullable) NSData *token;

/**
 * IM 控制台上传的 VoIP 证书 ID
 */
@property (nonatomic, assign) NSInteger certificateID;

@end

NS_ASSUME_NONNULL_END
