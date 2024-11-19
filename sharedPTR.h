#include <memory>
#include <iostream>

template<class T, class TDeleter = std::default_delete<T>>

class SharedPTR {
    typedef typename std::remove_all_extents<T>::type Type;
    using t_SharedPTR = SharedPTR<Type, TDeleter>;
private:
    struct ControlBlock{
        Type *pObj;
        int *refCount;
        TDeleter deleter;

        explicit ControlBlock(Type *pObject) : pObj(pObject), refCount(new int(1)), deleter(TDeleter()) {}

        ~ControlBlock() {
            deleter(pObj);
            delete refCount;
        }

    };

    ControlBlock *controlBlock;

public:
    // Constructors and destructor
    SharedPTR() : controlBlock(nullptr) {}

    explicit SharedPTR(nullptr_t) : controlBlock(nullptr) {}

    explicit SharedPTR(Type *pObject) : controlBlock(new ControlBlock(pObject)) {}


    explicit SharedPTR(const t_SharedPTR &other) : controlBlock(other.controlBlock) {
        if (controlBlock) {
            ++(*controlBlock->refCount);
        }
    }

    explicit SharedPTR(t_SharedPTR &&other) noexcept : controlBlock(other.controlBlock) {
        other.controlBlock = nullptr;
    }

    ~SharedPTR() {
        release();
    }

// Assignment
    SharedPTR& operator=(const t_SharedPTR &other) {
        if (this != &other) {
            release();
            controlBlock = other.controlBlock;
            if (controlBlock) {
                ++(*controlBlock->refCount);
            }
        }
        return *this;
    }

    SharedPTR& operator=(t_SharedPTR &&other) noexcept {
        std::swap(controlBlock, other.controlBlock);
        other.release();
        return *this;
    }

    SharedPTR& operator=(Type* pObject) {
        reset(pObject);
        return *this;
    }

// Observers
    Type& operator*() const {
        if (!controlBlock) {return NULL;}
        else {return *controlBlock->pObj;}
    }

    Type* operator->() const {
        if (controlBlock) {
            return controlBlock->pObj;
        }
        else {
            throw std::runtime_error("ControlBlock is nullptr");
        }
    }

    Type* get() const {
        if (controlBlock) {
            return controlBlock->pObj;
        }
        else {
            throw std::runtime_error("ControlBlock is nullptr");
        }
    }

    TDeleter& get_deleter() {
        if (controlBlock) {
            return controlBlock->deleter;
        }
        return std::default_delete<Type>();
    }

    size_t use_count() {
        if (controlBlock) {
            return *controlBlock->refCount;
        }
        return 0;
    }

    explicit operator bool() const {
        if (controlBlock) {
            return controlBlock->pObj != nullptr;
        }
        return false;
    }

// Modifiers
    void release() {
        if (controlBlock) {
            if (--(*controlBlock->refCount) == 0) {
                delete controlBlock;
            }
            controlBlock = nullptr;
        }
    }

    void reset(Type* pObject = nullptr) {
        if (pObject) {
            if (!controlBlock || controlBlock->pObj != pObject) {
                release();
                controlBlock = new ControlBlock(pObject);
            }
        }
        else {
            release();
        }
//        release();
//        if (pObject) {
//            controlBlock = new ControlBlock(pObject);
//        }
    }

    void swap(t_SharedPTR &sharedPTR) {
        std::swap(controlBlock, sharedPTR.controlBlock);
    }

};

template <class Type, class TDeleter = std::default_delete<Type>, class... Args>

SharedPTR<Type, TDeleter> make_shared(Args&&... args) {
    return SharedPTR<Type, TDeleter>(new Type(std::forward<Args>(args)...));
}