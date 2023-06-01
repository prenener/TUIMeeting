/////////////////////////////////////////////////////////////////////
//
//                     腾讯云通信服务 IMSDK
//
//  模块名称：V2TIMManager+Group
//
//  群组高级接口，里面包含了群组的高级功能，比如群成员邀请、非群成员申请进群等操作接口。
//
/////////////////////////////////////////////////////////////////////

#import "V2TIMManager.h"
#import "V2TIMManager+Message.h"
#import "V2TIMManager+Conversation.h"

@class V2TIMGroupMemberOperationResult;
@class V2TIMGroupApplicationResult;
@class V2TIMCreateGroupMemberInfo;
@class V2TIMGroupInfo;
@class V2TIMGroupInfoResult;
@class V2TIMTopicInfo;
@class V2TIMTopicInfoResult;
@class V2TIMTopicOperationResult;
@class V2TIMGroupApplication;
@class V2TIMGroupSearchParam;
@class V2TIMGroupMemberSearchParam;
@class V2TIMGroupAtInfo;

/////////////////////////////////////////////////////////////////////////////////
//
//                         群相关的高级接口
//
/////////////////////////////////////////////////////////////////////////////////

V2TIM_EXPORT @interface V2TIMManager (Group)

/// 获取已加入群列表成功回调
typedef void (^V2TIMGroupInfoListSucc)(NSArray<V2TIMGroupInfo *> *groupList);
/// 获取指定群列表成功回调
typedef void (^V2TIMGroupInfoResultListSucc)(NSArray<V2TIMGroupInfoResult *> *groupResultList);
/// 获取群属性列表成功回调
typedef void (^V2TIMGroupAttributeListSucc)(NSMutableDictionary<NSString *,NSString *> *groupAttributeList);
/// 获取群成员列表成功回调
typedef void (^V2TIMGroupMemberInfoListSucc)(NSArray<V2TIMGroupMemberFullInfo *> *memberList);
/// 获取指定群成员列表成功回调
typedef void (^V2TIMGroupMemberInfoResultSucc)(uint64_t nextSeq, NSArray<V2TIMGroupMemberFullInfo *> * memberList);
/// 搜索群成员列表成功回调
typedef void (^V2TIMGroupMemberInfoListSearchSucc)(NSDictionary<NSString *, NSArray<V2TIMGroupMemberFullInfo *> *> *memberList);
/// 群成员操作成功回调
typedef void (^V2TIMGroupMemberOperationResultListSucc)(NSArray<V2TIMGroupMemberOperationResult*> * resultList);
/// 获取好友申请列表成功回调
typedef void (^V2TIMGroupApplicationResultSucc)(V2TIMGroupApplicationResult *result);
/// 获取群在线人数成功回调
typedef void (^V2TIMGroupOnlineMemberCountSucc)(NSInteger count);
/// 操作话题列表结果
typedef void(^V2TIMTopicOperationResultSucc)(NSMutableArray<V2TIMTopicOperationResult *> *resultList);
/// 获取话题列表结果
typedef void(^V2TIMTopicInfoResultListSucc)(NSMutableArray<V2TIMTopicInfoResult *> *resultList);
/// 创建话题成功回调
typedef void (^V2TIMCreateTopicSucc)(NSString * topicID);
/// 群计数器操作成功的回调
typedef void (^V2TIMGroupCounterResultSucc)(NSDictionary<NSString *, NSNumber *> *groupCounters);

/// 加群选项
typedef NS_ENUM(NSInteger, V2TIMGroupAddOpt) {
    V2TIM_GROUP_ADD_FORBID                 = 0,  ///< 禁止加群
    V2TIM_GROUP_ADD_AUTH                   = 1,  ///< 需要管理员审批
    V2TIM_GROUP_ADD_ANY                    = 2,  ///< 任何人可以加入
};

///  群组操作结果
typedef NS_ENUM(NSInteger, V2TIMGroupMemberResult) {
    V2TIM_GROUP_MEMBER_RESULT_FAIL         = 0,  ///< 操作失败
    V2TIM_GROUP_MEMBER_RESULT_SUCC         = 1,  ///< 操作成功
    V2TIM_GROUP_MEMBER_RESULT_INVALID      = 2,  ///< 无效操作，加群时已经是群成员，移除群组时不在群内
    V2TIM_GROUP_MEMBER_RESULT_PENDING      = 3,  ///< 等待处理，邀请入群时等待审批
    V2TIM_GROUP_MEMBER_RESULT_OVERLIMIT    = 4,  ///< 操作失败，创建群指定初始群成员列表或邀请入群时，被邀请者加入的群总数超限
};

/// 群成员角色过滤方式
typedef NS_ENUM(NSInteger, V2TIMGroupMemberFilter) {
    V2TIM_GROUP_MEMBER_FILTER_ALL          = 0x00,  ///< 全部成员
    V2TIM_GROUP_MEMBER_FILTER_OWNER        = 0x01,  ///< 群主
    V2TIM_GROUP_MEMBER_FILTER_ADMIN        = 0x02,  ///< 管理员
    V2TIM_GROUP_MEMBER_FILTER_COMMON       = 0x04,  ///< 普通成员
};

/// 群组未决请求类型
typedef NS_ENUM(NSInteger, V2TIMGroupApplicationType) {
    V2TIM_GROUP_JOIN_APPLICATION_NEED_APPROVED_BY_ADMIN   = 0x0,         ///< 需要群主或管理员审批的申请加群请求
    V2TIM_GROUP_INVITE_APPLICATION_NEED_APPROVED_BY_INVITEE   = 0x1,     ///< 需要被邀请者同意的邀请入群请求
    V2TIM_GROUP_INVITE_APPLICATION_NEED_APPROVED_BY_ADMIN   = 0x2,       ///< 需要群主或管理员审批的邀请入群请求
};

/// 群组已决标志
typedef NS_ENUM(NSInteger, V2TIMGroupApplicationHandleStatus) {
    V2TIM_GROUP_APPLICATION_HANDLE_STATUS_UNHANDLED           = 0,  ///< 未处理
    V2TIM_GROUP_APPLICATION_HANDLE_STATUS_HANDLED_BY_OTHER    = 1,  ///< 被他人处理
    V2TIM_GROUP_APPLICATION_HANDLE_STATUS_HANDLED_BY_SELF     = 2,  ///< 自己已处理
};

/// 群组已决结果
typedef NS_ENUM(NSInteger, V2TIMGroupApplicationHandleResult) {
    V2TIM_GROUP_APPLICATION_HANDLE_RESULT_REFUSE = 0,  ///< 拒绝申请
    V2TIM_GROUP_APPLICATION_HANDLE_RESULT_AGREE  = 1,  ///< 同意申请
};

/////////////////////////////////////////////////////////////////////////////////
//                         群管理
/////////////////////////////////////////////////////////////////////////////////

/**
 *  1.1 创建自定义群组（高级版本：可以指定初始的群成员）
 *
 *  @param info 自定义群组信息，可以设置 groupID | groupType | groupName | notification | introduction | faceURL 字段
 *  @param memberList 指定初始的群成员（直播群 AVChatRoom 不支持指定初始群成员，memberList 请传 nil）
 *
 *  @note
 *  - 邀请的群成员个数不能超过 20（7.1 及其以上版本开始限制）
 *  - 其他限制请参考 V2TIMManager.h -> createGroup 注释
 */
- (void)createGroup:(V2TIMGroupInfo*)info memberList:(NSArray<V2TIMCreateGroupMemberInfo *>*) memberList succ:(V2TIMCreateGroupSucc)succ fail:(V2TIMFail)fail;

/**
 *  1.2 获取当前用户已经加入的群列表
 *
 *  @note
 *  - 直播群（AVChatRoom）不支持该 API
 *  - 该接口有频限检测，SDK 限制调用频率为 1 秒 10 次，超过限制后会报 ERR_SDK_COMM_API_CALL_FREQUENCY_LIMIT （7008）错误
 */
- (void)getJoinedGroupList:(V2TIMGroupInfoListSucc)succ fail:(V2TIMFail)fail;

/////////////////////////////////////////////////////////////////////////////////
//                         群资料管理
/////////////////////////////////////////////////////////////////////////////////

/**
 * 2.1 拉取群资料
 *
 *  @param groupIDList 群组 ID 列表
 */
- (void)getGroupsInfo:(NSArray<NSString *> *)groupIDList succ:(V2TIMGroupInfoResultListSucc)succ fail:(V2TIMFail)fail;

/**
 *  2.2 搜索群列表（5.4.666 及以上版本支持）
 * @note 该功能为 IM 旗舰版功能，[购买旗舰版套餐包](https://buy.cloud.tencent.com/avc?from=17474)后可使用，详见[价格说明](https://cloud.tencent.com/document/product/269/11673?from=17176#.E5.9F.BA.E7.A1.80.E6.9C.8D.E5.8A.A1.E8.AF.A6.E6.83.85)
 */
- (void)searchGroups:(V2TIMGroupSearchParam *)searchParam succ:(V2TIMGroupInfoListSucc)succ fail:(V2TIMFail)fail;

/**
 *  2.3 修改群资料
 */
- (void)setGroupInfo:(V2TIMGroupInfo *)info succ:(V2TIMSucc)succ fail:(V2TIMFail)fail;

/**
 *  2.4 初始化群属性，会清空原有的群属性列表
 *
 * @note
 * attributes 的使用限制如下：
 *  - 6.7 及其以前版本，只支持 AVChatRoom 直播群；
 *  - 从 6.8 版本开始，同时支持 AVChatRoom、Public、Meeting、Work 四种群类型；
 *  - 从 7.0 版本开始，除了话题外，群属性支持所有的群类型；
 *  - key 最多支持 16 个，长度限制为 32 字节；
 *  - value 长度限制为 4k；
 *  - 总的 attributes（包括 key 和 value）限制为 16k；
 *  - initGroupAttributes、setGroupAttributes、deleteGroupAttributes 接口合并计算， SDK 限制为 5 秒 10 次，超过后回调 8511 错误码；后台限制 1 秒 5 次，超过后返回 10049 错误码；
 *  - getGroupAttributes 接口 SDK 限制 5 秒 20 次；
 *  - 从 5.6 版本开始，当每次APP启动后初次修改群属性时，请您先调用 getGroupAttributes 拉取到最新的群属性之后，再发起修改操作；
 *  - 从 5.6 版本开始，当多个用户同时修改同一个群属性时，只有第一个用户可以执行成功，其它用户会收到 10056 错误码；收到这个错误码之后，请您调用 getGroupAttributes 把本地保存的群属性更新到最新之后，再发起修改操作。
 */
- (void)initGroupAttributes:(NSString*)groupID attributes:(NSDictionary<NSString *,NSString *> *)attributes succ:(V2TIMSucc)succ fail:(V2TIMFail)fail;

/**
 *  2.5 设置群属性，已有该群属性则更新其 value 值，没有该群属性则添加该群属性。
 *  @note
 *   - 6.7 及其以前版本，只支持 AVChatRoom 直播群；
 *   - 从 6.8 版本开始，同时支持 AVChatRoom、Public、Meeting、Work 四种群类型；
 *   - 从 7.0 版本开始，除了话题外，群属性支持所有的群类型。
 */
- (void)setGroupAttributes:(NSString*)groupID attributes:(NSDictionary<NSString *,NSString *> *)attributes succ:(V2TIMSucc)succ fail:(V2TIMFail)fail;

/**
 *  2.6 删除群指定属性，keys 传 nil 则清空所有群属性。
 *  @note
 *   - 6.7 及其以前版本，只支持 AVChatRoom 直播群；
 *   - 从 6.8 版本开始，同时支持 AVChatRoom、Public、Meeting、Work 四种群类型；
 *   - 从 7.0 版本开始，除了话题外，群属性支持所有的群类型。
 */
- (void)deleteGroupAttributes:(NSString*)groupID keys:(NSArray<NSString *> *)keys succ:(V2TIMSucc)succ fail:(V2TIMFail)fail;

/**
 *  2.7 获取群指定属性，keys 传 nil 则获取所有群属性。
 *  @note
 *   - 6.7 及其以前版本，只支持 AVChatRoom 直播群；
 *   - 从 6.8 版本开始，同时支持 AVChatRoom、Public、Meeting、Work 四种群类型；
 *   - 从 7.0 版本开始，除了话题外，群属性支持所有的群类型。
 */
- (void)getGroupAttributes:(NSString*)groupID keys:(NSArray<NSString *> *)keys succ:(V2TIMGroupAttributeListSucc)succ fail:(V2TIMFail)fail;

/**
 * 2.8 获取指定群在线人数
 *
 * @param groupID 群id
 * @param succ 成功回调
 * @param fail 失败回调
 *
 * @note 请注意
 * - 目前只支持：直播群（ AVChatRoom）。
 */
- (void)getGroupOnlineMemberCount:(NSString*)groupID succ:(V2TIMGroupOnlineMemberCountSucc)succ fail:(V2TIMFail)fail;

/**
 * 2.9 设置群计数器（7.0 及其以上版本支持）
 *
 * @note
 *  - 该计数器的 key 如果存在，则直接更新计数器的 value 值；如果不存在，则添加该计数器的 key-value；
 *  - 当群计数器设置成功后，在 succ 回调中会返回最终成功设置的群计数器信息；
 *  - 除了社群和话题，群计数器支持所有的群组类型。
 */
- (void)setGroupCounters:(NSString *)groupID counters:(NSDictionary<NSString *, NSNumber *> *)counters succ:(V2TIMGroupCounterResultSucc)succ fail:(V2TIMFail)fail;

/**
 * 2.10 获取群计数器（7.0 及其以上版本支持）
 *
 * @note
 *  - 如果 keys 为空，则表示获取群内的所有计数器；
 *  - 除了社群和话题，群计数器支持所有的群组类型。
 */
- (void)getGroupCounters:(NSString *)groupID keys:(NSArray<NSString *> *)keys succ:(V2TIMGroupCounterResultSucc)succ fail:(V2TIMFail)fail;

/**
 * 2.11 递增群计数器（7.0 及其以上版本支持）
 *
 * @param groupID 群 ID
 * @param key 群计数器的 key
 * @param value 群计数器的递增的变化量，计数器 key 对应的 value 变更方式为： new_value = old_value + value
 * @param succ 成功后的回调，会返回当前计数器做完递增操作后的 value
 * @param fail 失败的回调
 *
 * @note
 *  - 该计数器的 key 如果存在，则直接在当前值的基础上根据传入的 value 作递增操作；反之，添加 key，并在默认值为 0 的基础上根据传入的 value 作递增操作；
 *  - 除了社群和话题，群计数器支持所有的群组类型。
 */
- (void)increaseGroupCounter:(NSString *)groupID key:(NSString *)key value:(NSInteger)value succ:(V2TIMGroupCounterResultSucc)succ fail:(V2TIMFail)fail;

/**
 * 2.12 递减群计数器（7.0 及其以上版本支持）
 *
 * @param groupID 群 ID
 * @param key 群计数器的 key
 * @param value 群计数器的递减的变化量，计数器 key 对应的 value 变更方式为： new_value = old_value - value
 * @param succ 成功后的回调，会返回当前计数器做完递减操作后的 value
 * @param fail 失败的回调
 *
 * @note
 *  - 该计数器的 key 如果存在，则直接在当前值的基础上根据传入的 value 作递减操作；反之，添加 key，并在默认值为 0 的基础上根据传入的 value 作递减操作
 *  - 除了社群和话题，群计数器支持所有的群组类型。
 */
- (void)decreaseGroupCounter:(NSString *)groupID key:(NSString *)key value:(NSInteger)value succ:(V2TIMGroupCounterResultSucc)succ fail:(V2TIMFail)fail;

/////////////////////////////////////////////////////////////////////////////////
//                         群成员管理
/////////////////////////////////////////////////////////////////////////////////
/**
 *  3.1 获取群成员列表
 *
 *  @param filter   指定群成员类型。
 *  @param nextSeq  分页拉取标志，第一次拉取填 0，回调成功如果 nextSeq 不为零，需要分页，传入再次拉取，直至为 0。
 *
 *  @note
 *  - 普通群（工作群、会议群、公开群、社群）的限制：
 *  1. filter 只能设置为 V2TIMGroupMemberFilter 定义的数值，SDK 会返回指定角色的成员。
 *
 *  - 直播群（AVChatRoom）的限制：
 *  1. 如果设置 filter 为 V2TIMGroupMemberFilter 定义的数值，SDK 返回全部成员。返回的人数规则为：旗舰版支持拉取最近入群群成员最多 1000 人，新进来的成员排在前面（6.3 及以上版本支持，需要先在 [控制台](https://console.cloud.tencent.com/im) 开启开关；非旗舰版支持拉取最近入群群成员最多 31 人，新进来的成员排在前面。
 *  2. 如果设置 filter 为群成员自定义标记，旗舰版支持拉取指定标记的成员列表。标记群成员的设置请参考 markGroupMemberList:memberList:markType:enableMark:succ:fail: API。
 *  3. 程序重启后，请重新加入群组，否则拉取群成员会报 10007 错误码。
 *  4. 群成员资料信息仅支持 userID | nickName | faceURL | role 字段。
 */
- (void)getGroupMemberList:(NSString*)groupID filter:(uint32_t)filter nextSeq:(uint64_t)nextSeq succ:(V2TIMGroupMemberInfoResultSucc)succ fail:(V2TIMFail)fail;

/**
 *  3.2 指定的群成员资料
 */
- (void)getGroupMembersInfo:(NSString*)groupID memberList:(NSArray<NSString*>*)memberList succ:(V2TIMGroupMemberInfoListSucc)succ fail:(V2TIMFail)fail;

/**
 *  3.3 搜索指定的群成员资料（5.4.666 及以上版本支持）
 *
 * @param searchParam 搜索参数
 * @note 该功能为 IM 旗舰版功能，[购买旗舰版套餐包](https://buy.cloud.tencent.com/avc?from=17474)后可使用，详见[价格说明](https://cloud.tencent.com/document/product/269/11673?from=17176#.E5.9F.BA.E7.A1.80.E6.9C.8D.E5.8A.A1.E8.AF.A6.E6.83.85)
 */
- (void)searchGroupMembers:(V2TIMGroupMemberSearchParam *)searchParam
                      succ:(V2TIMGroupMemberInfoListSearchSucc)succ
                      fail:(V2TIMFail)fail;
/**
 *  3.4 修改指定的群成员资料
 */
- (void)setGroupMemberInfo:(NSString*)groupID info:(V2TIMGroupMemberFullInfo *)info succ:(V2TIMSucc)succ fail:(V2TIMFail)fail;

/**
 *  3.5 禁言（只有管理员或群主能够调用）
 *
 *  @param seconds 禁言时间长度，单位秒，表示调用该接口成功后多少秒内不允许被禁言用户再发言。
 */
- (void)muteGroupMember:(NSString*)groupID member:(NSString*)userID muteTime:(uint32_t)seconds succ:(V2TIMSucc)succ fail:(V2TIMFail)fail;

/**
 *  3.6 邀请他人入群
 *
 *  @note 请注意不同类型的群有如下限制：
 *  - 工作群（Work）：群里的任何人都可以邀请其他人进群。
 *  - 会议群（Meeting）和公开群（Public）：只有通过rest api 使用 App 管理员身份才可以邀请其他人进群。
 *  - 直播群（AVChatRoom）：不支持此功能。
 *  - 单次邀请的群成员个数不能超过 20（7.1 及其以上版本开始限制）。
 */
- (void)inviteUserToGroup:(NSString*)groupID userList:(NSArray<NSString *>*)userList succ:(V2TIMGroupMemberOperationResultListSucc)succ fail:(V2TIMFail)fail;

/**
 *  3.7 踢人（直播群踢人从 6.6 版本开始支持，需要您购买旗舰版套餐）
 *
 *  @note 请注意不同类型的群有如下限制：
 * - 工作群（Work）：只有群主或 APP 管理员可以踢人。
 * - 公开群（Public）、会议群（Meeting）：群主、管理员和 APP 管理员可以踢人
 * - 直播群（AVChatRoom）：6.6 之前版本只支持禁言（muteGroupMember），不支持踢人。6.6 及以上版本支持禁言和踢人。
 */
- (void)kickGroupMember:(NSString*)groupID memberList:(NSArray<NSString *>*)memberList reason:(NSString*)reason succ:(V2TIMGroupMemberOperationResultListSucc)succ fail:(V2TIMFail)fail;

/**
 *  3.8 切换群成员的角色
 *
 *  @note 请注意不同类型的群有如下限制：
 *  - 公开群（Public）和会议群（Meeting）：只有群主才能对群成员进行普通成员和管理员之间的角色切换。
 *  - 其他群不支持设置群成员角色。
 *  - 转让群组请调用 @ref transferGroupOwner 接口。
 *  - 会议群（Meeting）切换群成员角色之后，不会有 onGrantAdministrator 和 onRevokeAdministrator 通知回调
 *  - 切换的角色支持普通群成员（ V2TIM_GROUP_MEMBER_ROLE_MEMBER） 和管理员（V2TIM_GROUP_MEMBER_ROLE_ADMIN
 */
- (void)setGroupMemberRole:(NSString*)groupID member:(NSString *)userID newRole:(uint32_t)role succ:(V2TIMSucc)succ fail:(V2TIMFail)fail;

/**
 *  3.9 标记群成员(从 6.6 版本开始支持，需要您购买旗舰版套餐)
 *
 *  @param groupID 群 ID。
 *  @param memberList 群成员 ID 列表。
 *  @param markType 标记类型。数字类型，大于等于 1000，您可以自定义，一个直播群里最多允许定义 10 个标记。
 *  @param enableMark YES 表示添加标记，NO 表示移除标记。
 *  @note 请注意
 *  - 仅支持直播群。
 *  - 只有群主才有权限标记群组中其他人。
 */
- (void)markGroupMemberList:(NSString *)groupID memberList:(NSArray<NSString *> *)memberList markType:(uint32_t)markType enableMark:(BOOL)enableMark succ:(V2TIMSucc)succ fail:(V2TIMFail)fail;

/**
 *  3.10 转让群主
 *
 *  @note 请注意不同类型的群有如下限制：
 *  - 普通类型的群（Work、Public、Meeting）：只有群主才有权限进行群转让操作。
 *  - 直播群（AVChatRoom）：不支持转让群主。
 */
- (void)transferGroupOwner:(NSString*)groupID member:(NSString*)userID succ:(V2TIMSucc)succ fail:(V2TIMFail)fail;

/////////////////////////////////////////////////////////////////////////////////
//                         加群申请
/////////////////////////////////////////////////////////////////////////////////

/**
 * 4.1 获取加群申请列表
 * @note 最多支持50个
*/
- (void)getGroupApplicationList:(V2TIMGroupApplicationResultSucc)succ fail:(V2TIMFail)fail;

/**
 *  4.2 同意某一条加群申请
 */
- (void)acceptGroupApplication:(V2TIMGroupApplication *)application reason:(NSString*)reason succ:(V2TIMSucc)succ fail:(V2TIMFail)fail;

/**
 *  4.3 拒绝某一条加群申请
 */
- (void)refuseGroupApplication:(V2TIMGroupApplication *)application reason:(NSString*)reason succ:(V2TIMSucc)succ fail:(V2TIMFail)fail;

/**
 *  4.4 标记申请列表为已读
 */
- (void)setGroupApplicationRead:(V2TIMSucc)succ fail:(V2TIMFail)fail;

/////////////////////////////////////////////////////////////////////////////////
//                         社群-话题
/////////////////////////////////////////////////////////////////////////////////
/**
 * 5.1 获取当前用户已经加入的支持话题的社群列表
 */
- (void)getJoinedCommunityList:(V2TIMGroupInfoListSucc)succ fail:(V2TIMFail)fail;

/**
 * 5.2 创建话题
 */
- (void)createTopicInCommunity:(NSString *)groupID topicInfo:(V2TIMTopicInfo *)topicInfo succ:(V2TIMCreateTopicSucc)succ fail:(V2TIMFail)fail;

/**
 * 5.3 删除话题
 */
- (void)deleteTopicFromCommunity:(NSString *)groupID topicIDList:(NSArray<NSString *>*)topicIDList succ:(V2TIMTopicOperationResultSucc)succ fail:(V2TIMFail)fail;

/**
 * 5.4 修改话题信息
 */
- (void)setTopicInfo:(V2TIMTopicInfo *)topicInfo succ:(V2TIMSucc)succ fail:(V2TIMFail)fail;

/**
  * 5.5 获取话题列表。
  * @note: topicIDList 传空时，获取此社群下的所有话题列表
  */
- (void)getTopicInfoList:(NSString *)groupID topicIDList:(NSArray<NSString *>*)topicIDList succ:(V2TIMTopicInfoResultListSucc)succ fail:(V2TIMFail)fail;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//             群基本资料（可以通过 getGroupInfo 获取，不支持由客户自行创建）
//
/////////////////////////////////////////////////////////////////////////////////
/// 群资料
V2TIM_EXPORT @interface V2TIMGroupInfo : NSObject

/**
 * 群组 ID
 *
 * @note 自定义群组 ID 必须为可打印 ASCII 字符（0x20-0x7e），最长48个字节，且前缀不能为 @TGS#（避免与默认分配的群组 ID 混淆）
 */
@property(nonatomic,strong) NSString* groupID;

/// 群类型
@property(nonatomic,strong) NSString* groupType;

/**
 * 社群是否支持创建话题
 * @note 只在群类型为 Community 时有效
 */
@property(nonatomic,assign) BOOL isSupportTopic;

/**
 * 群名称
 *
 * @note 群名称最长30字节
 */
@property(nonatomic,strong) NSString* groupName;

/**
 * 群公告
 *
 * @note 群公告最长300字节
 */
@property(nonatomic,strong) NSString* notification;

/**
 * 群简介
 *
 * @note 群简介最长240字节
 */
@property(nonatomic,strong) NSString* introduction;

/**
 * 群头像
 *
 * @note 群头像 URL 最长100字节
 */
@property(nonatomic,strong) NSString* faceURL;

/// 是否全员禁言
@property(nonatomic,assign) BOOL allMuted;

///设置群自定义字段需要两个步骤：
///1.在 [控制台](https://console.cloud.tencent.com/im) (功能配置 -> 群自定义字段) 配置群自定义字段的 key 值，Key 为 String 类型，长度不超过 16 字节。
///2.调用 setGroupInfo 接口设置该字段，value 为 NSData 数据，长度不超过 512 字节。
///@note 该字段主要用于 V1 和 V2 版本的兼容，如果您直接使用的是 V2 版本的 API ，建议使用 initGroupAttributes 接口设置群属性，其设置更灵活（无需控制台配置），支持的存储也更大（最大支持 16K）
@property(nonatomic,strong) NSDictionary<NSString *,NSData *>* customInfo;

/// 群创建人/管理员
@property(nonatomic,strong,readonly) NSString *owner;

/// 群创建时间
@property(nonatomic,assign,readonly) uint32_t createTime;

/// 申请进群是否需要管理员审批：工作群（Work）默认值为 V2TIM_GROUP_ADD_FORBID，即默认不允许申请入群，您可以修改该字段打开申请入群方式。
@property(nonatomic,assign) V2TIMGroupAddOpt groupAddOpt;

/// 邀请进群是否需要管理员审批 （从 7.1 版本开始支持）
/// - 除工作群（Work）之外的其他群类型默认值都为 V2TIM_GROUP_ADD_FORBID，即默认不允许邀请入群，您可以修改该字段打开邀请入群方式。
/// - 直播群、社群和话题默认不允许邀请入群，也不支持修改。
@property(nonatomic,assign) V2TIMGroupAddOpt groupApproveOpt;

/// 群最近一次群资料修改时间
@property(nonatomic,assign,readonly) uint32_t lastInfoTime;

/// 群最近一次发消息时间
@property(nonatomic,assign,readonly) uint32_t lastMessageTime;

/// 已加入的群成员数量
@property(nonatomic,assign,readonly) uint32_t memberCount;

/// 在线的群成员数量
@property(nonatomic,assign,readonly) uint32_t onlineCount;

/// 最多允许加入的群成员数量
/// @note 各类群成员人数限制详见: https://cloud.tencent.com/document/product/269/1502#.E7.BE.A4.E7.BB.84.E9.99.90.E5.88.B6.E5.B7.AE.E5.BC.82
@property(nonatomic,assign,readonly) uint32_t memberMaxCount;

/// 当前用户在此群组中的角色（V2TIMGroupMemberRole），切换角色请调用 setGroupMemberRole 接口
@property(nonatomic,assign,readonly) uint32_t role;

/// 当前用户在此群组中的消息接收选项,修改群消息接收选项请调用 setGroupReceiveMessageOpt 接口
@property(nonatomic,assign,readonly) V2TIMReceiveMessageOpt recvOpt;

/// 当前用户在此群中的加入时间，不支持设置，系统自动生成
@property(nonatomic,assign,readonly) uint32_t joinTime;

@end

/// 获取群组资料结果
V2TIM_EXPORT @interface V2TIMGroupInfoResult : NSObject

/// 结果 0：成功；非0：失败
@property(nonatomic,assign) int resultCode;

/// 如果获取失败，会返回错误信息
@property(nonatomic,strong) NSString *resultMsg;

/// 如果获取成功，会返回对应的 info
@property(nonatomic,strong) V2TIMGroupInfo *info;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//             话题基本资料（可以通过 getTopics 获取，不支持由客户自行创建）
//
/////////////////////////////////////////////////////////////////////////////////
V2TIM_EXPORT @interface V2TIMTopicInfo : NSObject

/// 话题 ID
@property(nonatomic, strong) NSString *topicID;

/// 话题名称
@property(nonatomic, strong) NSString *topicName;

/// 话题头像
@property(nonatomic, strong) NSString *topicFaceURL;

/// 话题介绍
@property(nonatomic, strong) NSString *introduction;

/// 话题公告
@property(nonatomic, strong) NSString *notification;

/// 话题全员禁言
@property(nonatomic, assign) BOOL isAllMuted;

/// 当前用户在话题中的禁言时间
@property(nonatomic, assign, readonly) uint32_t selfMuteTime;

/// 话题自定义字段
@property(nonatomic, strong) NSString *customString;

/// 话题消息接收选项，修改话题消息接收选项请调用 setGroupReceiveMessageOpt 接口
@property(nonatomic, assign, readonly) V2TIMReceiveMessageOpt recvOpt;

/// 话题草稿
@property(nonatomic, strong) NSString *draftText;

/// 话题消息未读数量
@property(nonatomic, assign, readonly) uint64_t unreadCount;

/// 话题 lastMessage
@property(nonatomic,strong,readonly) V2TIMMessage *lastMessage;

/// 话题 at 信息列表
@property(nonatomic, strong, readonly) NSArray<V2TIMGroupAtInfo *> *groupAtInfolist;
@end

/////////////////////////////////////////////////////////////////////////////////
//
//             V2TIMTopicOperationResult
//
/////////////////////////////////////////////////////////////////////////////////
V2TIM_EXPORT @interface V2TIMTopicOperationResult : NSObject

/// 结果 0：成功；非0：失败
@property(nonatomic, assign)  int errorCode;

/// 如果删除失败，会返回错误信息
@property(nonatomic, strong)  NSString *errorMsg;

/// 如果删除成功，会返回对应的 topicID
@property(nonatomic, strong)  NSString *topicID;
@end

/////////////////////////////////////////////////////////////////////////////////
//
//             V2TIMTopicInfoResult
//
/////////////////////////////////////////////////////////////////////////////////
V2TIM_EXPORT @interface V2TIMTopicInfoResult : NSObject

/// 结果 0：成功；非0：失败
@property(nonatomic, assign)  int errorCode;

/// 如果获取失败，会返回错误信息
@property(nonatomic, strong)  NSString *errorMsg;

/// 如果获取成功，会返回对应的 info
@property(nonatomic, strong)  V2TIMTopicInfo *topicInfo;
@end


/////////////////////////////////////////////////////////////////////////////////
//
//          群申请信息（可以通过 getGroupApplicationList 获取，不支持由客户自行创建）
//
/////////////////////////////////////////////////////////////////////////////////
/// 群申请信息
V2TIM_EXPORT @interface V2TIMGroupApplication : NSObject

/// 群组 ID
@property(nonatomic,strong,readonly) NSString* groupID;

/// 请求者 userID
@property(nonatomic,strong,readonly) NSString* fromUser;

/// 请求者昵称
@property(nonatomic,strong,readonly) NSString* fromUserNickName;

/// 请求者头像
@property(nonatomic,strong,readonly) NSString* fromUserFaceUrl;

/// 判决者id，有人请求加群:0，邀请其他人加群:被邀请人用户 ID
@property(nonatomic,strong,readonly) NSString* toUser;

/// 申请时间
@property(nonatomic,assign,readonly) uint64_t addTime;

/// 申请或邀请附加信息
@property(nonatomic,strong,readonly) NSString* requestMsg;

/// 审批信息：同意或拒绝信息
@property(nonatomic,strong,readonly) NSString* handledMsg;

/// 请求类型
@property(nonatomic,assign,readonly) V2TIMGroupApplicationType applicationType;

/// 处理标志
@property(nonatomic,assign,readonly) V2TIMGroupApplicationHandleStatus handleStatus;

/// 处理结果
@property(nonatomic,assign,readonly) V2TIMGroupApplicationHandleResult handleResult;

@end


/////////////////////////////////////////////////////////////////////////////////
//
//                        邀请其他人入群的操作结果
//
/////////////////////////////////////////////////////////////////////////////////
/// 邀请其他人入群的操作结果
V2TIM_EXPORT @interface V2TIMGroupMemberOperationResult : NSObject

/// 被操作成员
@property(nonatomic,strong) NSString* userID;

/// 返回状态
@property(nonatomic,assign) V2TIMGroupMemberResult result;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//                        创建群时指定群成员
//
/////////////////////////////////////////////////////////////////////////////////
/// 创建群时指定群成员
V2TIM_EXPORT @interface V2TIMCreateGroupMemberInfo : NSObject

/// 被操作成员
@property(nonatomic,strong) NSString* userID;

/** 群成员类型，需要注意一下事项：
 * 1. role 不设置或则设置为 V2TIM_GROUP_MEMBER_UNDEFINED，进群后默认为群成员。
 * 2. 工作群（Work）不支持设置 role 为管理员。
 * 3. 所有的群都不支持设置 role 为群主。
 */
@property(nonatomic,assign) uint32_t role;

@end


/////////////////////////////////////////////////////////////////////////////////
//
//                        加群申请列表（包含已处理和待处理的）
//
/////////////////////////////////////////////////////////////////////////////////
/// 加群申请列表
V2TIM_EXPORT @interface V2TIMGroupApplicationResult : NSObject

/// 未读的申请数量
@property(nonatomic,assign) uint64_t unreadCount;

/// 加群申请的列表
@property(nonatomic,strong) NSMutableArray<V2TIMGroupApplication *> * applicationList;
@end

/////////////////////////////////////////////////////////////////////////////////
//
//                        群搜索
//
/////////////////////////////////////////////////////////////////////////////////
V2TIM_EXPORT @interface V2TIMGroupSearchParam : NSObject

/// 搜索关键字列表，最多支持5个。
@property(nonatomic, strong) NSArray<NSString *> *keywordList;

/// 设置是否搜索群 ID。
@property(nonatomic, assign) BOOL isSearchGroupID;

/// 设置是否搜索群名称
@property(nonatomic, assign) BOOL isSearchGroupName;

@end

V2TIM_EXPORT @interface V2TIMGroupMemberSearchParam : NSObject

/// 指定群 ID 列表，若为 null 则搜索全部群中的群成员
@property(nonatomic, strong) NSArray<NSString *> *groupIDList;

/// 搜索关键字列表，最多支持5个
@property(nonatomic, strong) NSArray<NSString *> *keywordList;

/// 设置是否搜索群成员 userID
@property(nonatomic, assign) BOOL isSearchMemberUserID;

/// 设置是否搜索群成员昵称
@property(nonatomic, assign) BOOL isSearchMemberNickName;

/// 设置是否搜索群成员备注
@property(nonatomic, assign) BOOL isSearchMemberRemark;

/// 设置是否搜索群成员名片
@property(nonatomic, assign) BOOL isSearchMemberNameCard;

@end
