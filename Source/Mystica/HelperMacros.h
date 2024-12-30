#pragma once

#define MYSTICA_RETURN_IF_CANT_ENSURE_THAT(Condition) \
    if (!(ensure(Condition))) {                       \
        return;                                       \
    }

#define MYSTICA_RETURN_IF_CANT_ENSURE_THAT_VALUE(Condition, ReturnValue) \
    if (!(ensure(Condition))) {                                          \
        return ReturnValue;                                              \
    }

#define MYSTICA_LOG_NULL(CategoryName, Verbosity, NullItem) \
    UE_LOG(CategoryName, Verbosity, TEXT("%s is nullptr."), TEXT(#NullItem));

#define MYSTICA_IF_NULL_LOG_AND_RETURN(CategoryName, Verbosity, NullItem) \
    if (!NullItem) {                                                      \
        MYSTICA_LOG_NULL(CategoryName, Verbosity, NullItem)               \
        return;                                                           \
    }

#define MYSTICA_IF_NULL_LOG_AND_RETURN_VALUE(CategoryName, Verbosity, \
                                             NullItem, ReturnValue)   \
    if (!NullItem) {                                                  \
        MYSTICA_LOG_NULL(CategoryName, Verbosity, NullItem)           \
        return ReturnValue;                                           \
    }

#define MYSTICA_LOG_AND_RETURN_IF(Condition, CategoryName, Verbosity, Message) \
    if (Condition) {                                                           \
        UE_LOG(CategoryName, Verbosity, TEXT(Message));                        \
        return;                                                                \
    }

#define MYSTICA_LOG_AND_CONTINUE_IF(Condition, CategoryName, Verbosity, \
                                    Message)                            \
    if (Condition) {                                                    \
        UE_LOG(CategoryName, Verbosity, TEXT(Message));                 \
        continue;                                                       \
    }

#define MYSTICA_LOG_AND_RETURN_VALUE_IF(Condition, CategoryName, Verbosity, \
                                        Message, ReturnValue)               \
    if (Condition) {                                                        \
        UE_LOG(CategoryName, Verbosity, TEXT(Message));                     \
        return ReturnValue;                                                 \
    }

#define MYSTICA_RETURN_IF(Condition) \
    if (Condition) {                 \
        return;                      \
    }

#define MYSTICA_RETURN_VALUE_IF(Condition, ReturnValue) \
    if (Condition) {                                    \
        return ReturnValue;                             \
    }

#define MYSTICA_CONTINUE_IF(Condition) \
    if (Condition) {                   \
        continue;                      \
    }
