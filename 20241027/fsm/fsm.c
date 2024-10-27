/**
 * @file fsm.c
 * @brief fsm
 * @author ruleline (ruleline@outlook.com)
 * @since 2024-10-27
 *
 * @authors ruleline (ruleline@outlook.com)
 * @date 2024-10-27
 * @version 0.00.001
 *
 * @copyright ©2024 UNISAR
 *
 * @details
 * -----------------------------------------------------------------------------
 *    version   |    date    |     author     |             comments
 * ------------ | ---------- | -------------- | --------------------------------
 *   0.00.001   | 2024-10-27 |    ruleline    | 初版
 * -----------------------------------------------------------------------------
 */

#include "fsm.h"

/**
 * @brief 状态
 *
 */
enum STATE {
        STATE_A = 0, /**< 状态a */
        STATE_B = 1, /**< 状态b */
        STATE_C = 2, /**< 状态c */
        STATE_D = 3, /**< 状态d */
        STATE_MAX,
};

struct FSM;
/**
 * @brief 操作
 *
 */
struct OPS_HANDLER {
        int (*a)(struct FSM *self); /**< a操作 */
        int (*b)(struct FSM *self); /**< b操作 */
        int (*c)(struct FSM *self); /**< c操作 */
        int (*d)(struct FSM *self); /**< d操作 */
};

/**
 * @brief 内部操作
 *
 */
struct OPS_INTERNAL {
        int (*init)(struct FSM *self);          /**< 初始化操作 */
        int (*deinit)(struct FSM *self);        /**< 反初始化操作 */
        int (*run)(struct FSM *self);           /**< 运行操作 */
};

/**
 * @brief 外部操作
 *
 */
struct OPS_EXTERNAL {

};

/**
 * @brief 操作组
 *
 */
struct OPS {
        const struct OPS_HANDLER *handler;      /**< 操作 */
        const struct OPS_INTERNAL *internal;    /**< 内部操作 */
        const struct OPS_EXTERNAL *external;    /**< 外部操作 */
};

/**
 * @brief fsm
 *
 */
struct FSM {
        enum STATE state;       /**< 状态 */

        const struct OPS *ops;  /**< 操作 */
};

static inline int handler_a_(struct FSM *self);
static inline int handler_b_(struct FSM *self);
static inline int handler_c_(struct FSM *self);
static inline int handler_d_(struct FSM *self);

static inline int init_(struct FSM *self);
static inline int deinit_(struct FSM *self);
static inline int run_(struct FSM *self);

/**
 * @brief 操作
 *
 */
static const struct OPS_HANDLER handler = {
        .a = handler_a_,
        .b = handler_b_,
        .c = handler_c_,
        .d = handler_d_,
};

/**
 * @brief 内部操作
 *
 */
static const struct OPS_INTERNAL internal = {
        .init = init_,
        .deinit = deinit_,
        .run = run_,
};

/**
 * @brief 外部操作
 *
 */
static const struct OPS_EXTERNAL external = {

};

/**
 * @brief 操作组
 *
 */
static const struct OPS ops = {
        .handler = &handler,
        .internal = &internal,
        .external = &external,
};

/**
 * @brief fsm对象
 *
 */
static struct FSM fsm = {
        .state = STATE_MAX,

        .ops = &ops,
};

static const int (*handlers[STATE_MAX])(struct FSM *self) = {
        &handler_a_,
        &handler_b_,
        &handler_c_,
        &handler_d_,
};

/**
 * @brief a操作
 *
 * @param self fsm对象
 */
static inline int handler_a_(struct FSM *self)
{
        /* do something */
        self->state = STATE_B;
        return 0;
}

/**
 * @brief b操作
 *
 * @param self fsm对象
 */
static inline int handler_b_(struct FSM *self)
{
        /* do something */
        self->state = STATE_C;
        return 0;
}

/**
 * @brief c操作
 *
 * @param self fsm对象
 */
static inline int handler_c_(struct FSM *self)
{
        /* do something */
        self->state = STATE_B;
        return 0;
}

/**
 * @brief d操作
 *
 * @param self fsm对象
 */
static inline int handler_d_(struct FSM *self)
{
        /* do something */
        self->state = STATE_A;
        return 0;
}

/**
 * @brief 初始化操作
 *
 * @param self fsm对象
 * @return 0
 */
static inline int init_(struct FSM *self)
{
        // 初始化逻辑
        self->state = STATE_A;
        return 0;
}

/**
 * @brief 反初始化操作
 *
 * @param self fsm对象
 * @return 0
 */
static inline int deinit_(struct FSM *self)
{
        // 反初始化逻辑
        return 0;
}

/**
 * @brief 运行
 *
 * @param self fsm对象
 * @return 0
 */
static inline int run_(struct FSM *self)
{
        if (self->state >= STATE_MAX) return -1;

        handlers[self->state](self);
        return 0;
}

/**
 * @brief fsm初始化
 *
 */
void fsm_init(void)
{
        struct FSM *self = &fsm;
        self->ops->internal->init(self);
}

/**
 * @brief fsm反初始化
 *
 */
void fsm_deinit(void)
{
        struct FSM *self = &fsm;
        self->ops->internal->deinit(self);
}

/**
 * @brief fsm运行
 *
 */
void fsm_run(void)
{
        struct FSM *self = &fsm;
        self->ops->internal->run(self);
}
