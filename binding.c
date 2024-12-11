#include <assert.h>
#include <bare.h>
#include <js.h>
#include <stdint.h>
#include <uv.h>

typedef struct {
  uv_mutex_t handle;
} bare_atomics_mutex_t;

typedef struct {
  uv_sem_t handle;
} bare_atomics_semaphore_t;

typedef struct {
  uv_cond_t handle;
} bare_atomics_condition_t;

typedef struct {
  uv_barrier_t handle;
} bare_atomics_barrier_t;

static js_value_t *
bare_atomics_mutex_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bool recursive;
  err = js_get_value_bool(env, argv[0], &recursive);
  assert(err == 0);

  js_value_t *handle;

  bare_atomics_mutex_t *mutex;
  err = js_create_sharedarraybuffer(env, sizeof(bare_atomics_mutex_t), (void **) &mutex, &handle);
  assert(err == 0);

  if (recursive) {
    err = uv_mutex_init_recursive(&mutex->handle);
  } else {
    err = uv_mutex_init(&mutex->handle);
  }

  assert(err == 0);

  return handle;
}

static js_value_t *
bare_atomics_mutex_destroy(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_mutex_t *mutex;
  err = js_get_sharedarraybuffer_info(env, argv[0], (void **) &mutex, NULL);
  assert(err == 0);

  uv_mutex_destroy(&mutex->handle);

  return NULL;
}

static js_value_t *
bare_atomics_mutex_lock(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_mutex_t *mutex;
  err = js_get_sharedarraybuffer_info(env, argv[0], (void **) &mutex, NULL);
  assert(err == 0);

  uv_mutex_lock(&mutex->handle);

  return NULL;
}

static js_value_t *
bare_atomics_mutex_try_lock(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_mutex_t *mutex;
  err = js_get_sharedarraybuffer_info(env, argv[0], (void **) &mutex, NULL);
  assert(err == 0);

  err = uv_mutex_trylock(&mutex->handle);

  js_value_t *success;
  err = js_get_boolean(env, err == 0, &success);
  assert(err == 0);

  return success;
}

static js_value_t *
bare_atomics_mutex_unlock(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_mutex_t *mutex;
  err = js_get_sharedarraybuffer_info(env, argv[0], (void **) &mutex, NULL);
  assert(err == 0);

  uv_mutex_unlock(&mutex->handle);

  return NULL;
}

static js_value_t *
bare_atomics_semaphore_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  uint32_t value;
  err = js_get_value_uint32(env, argv[0], &value);
  assert(err == 0);

  js_value_t *handle;

  bare_atomics_semaphore_t *semaphore;
  err = js_create_sharedarraybuffer(env, sizeof(bare_atomics_semaphore_t), (void **) &semaphore, &handle);
  assert(err == 0);

  err = uv_sem_init(&semaphore->handle, value);
  assert(err == 0);

  return handle;
}

static js_value_t *
bare_atomics_semaphore_destroy(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_semaphore_t *semaphore;
  err = js_get_sharedarraybuffer_info(env, argv[0], (void **) &semaphore, NULL);
  assert(err == 0);

  uv_sem_destroy(&semaphore->handle);

  return NULL;
}

static js_value_t *
bare_atomics_semaphore_wait(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_semaphore_t *semaphore;
  err = js_get_sharedarraybuffer_info(env, argv[0], (void **) &semaphore, NULL);
  assert(err == 0);

  uv_sem_wait(&semaphore->handle);

  return NULL;
}

static js_value_t *
bare_atomics_semaphore_try_wait(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_semaphore_t *semaphore;
  err = js_get_sharedarraybuffer_info(env, argv[0], (void **) &semaphore, NULL);
  assert(err == 0);

  err = uv_sem_trywait(&semaphore->handle);

  js_value_t *success;
  err = js_get_boolean(env, err == 0, &success);
  assert(err == 0);

  return success;
}

static js_value_t *
bare_atomics_semaphore_post(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_semaphore_t *semaphore;
  err = js_get_sharedarraybuffer_info(env, argv[0], (void **) &semaphore, NULL);
  assert(err == 0);

  uv_sem_post(&semaphore->handle);

  return NULL;
}

static js_value_t *
bare_atomics_condition_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  js_value_t *handle;

  bare_atomics_condition_t *condition;
  err = js_create_sharedarraybuffer(env, sizeof(bare_atomics_condition_t), (void **) &condition, &handle);
  assert(err == 0);

  err = uv_cond_init(&condition->handle);
  assert(err == 0);

  return handle;
}

static js_value_t *
bare_atomics_condition_destroy(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_condition_t *condition;
  err = js_get_sharedarraybuffer_info(env, argv[0], (void **) &condition, NULL);
  assert(err == 0);

  uv_cond_destroy(&condition->handle);

  return NULL;
}

static js_value_t *
bare_atomics_condition_wait(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 3);

  bare_atomics_condition_t *condition;
  err = js_get_sharedarraybuffer_info(env, argv[0], (void **) &condition, NULL);
  assert(err == 0);

  bare_atomics_mutex_t *mutex;
  err = js_get_sharedarraybuffer_info(env, argv[1], (void **) &mutex, NULL);
  assert(err == 0);

  int64_t timeout;
  err = js_get_value_int64(env, argv[2], &timeout);
  assert(err == 0);

  js_value_t *success;

  if (timeout == -1) {
    uv_cond_wait(&condition->handle, &mutex->handle);

    err = js_get_boolean(env, true, &success);
    assert(err == 0);
  } else {
    err = uv_cond_timedwait(&condition->handle, &mutex->handle, timeout);

    err = js_get_boolean(env, err == 0, &success);
    assert(err == 0);
  }

  return success;
}

static js_value_t *
bare_atomics_condition_signal(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_condition_t *condition;
  err = js_get_sharedarraybuffer_info(env, argv[0], (void **) &condition, NULL);
  assert(err == 0);

  uv_cond_signal(&condition->handle);

  return NULL;
}

static js_value_t *
bare_atomics_condition_broadcast(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_condition_t *condition;
  err = js_get_sharedarraybuffer_info(env, argv[0], (void **) &condition, NULL);
  assert(err == 0);

  uv_cond_broadcast(&condition->handle);

  return NULL;
}

static js_value_t *
bare_atomics_barrier_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  uint32_t count;
  err = js_get_value_uint32(env, argv[0], &count);
  assert(err == 0);

  js_value_t *handle;

  bare_atomics_barrier_t *barrier;
  err = js_create_sharedarraybuffer(env, sizeof(bare_atomics_barrier_t), (void **) &barrier, &handle);
  assert(err == 0);

  err = uv_barrier_init(&barrier->handle, count);
  assert(err == 0);

  return handle;
}

static js_value_t *
bare_atomics_barrier_destroy(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_barrier_t *barrier;
  err = js_get_sharedarraybuffer_info(env, argv[0], (void **) &barrier, NULL);
  assert(err == 0);

  uv_barrier_destroy(&barrier->handle);

  return NULL;
}

static js_value_t *
bare_atomics_barrier_wait(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_barrier_t *barrier;
  err = js_get_sharedarraybuffer_info(env, argv[0], (void **) &barrier, NULL);
  assert(err == 0);

  err = uv_barrier_wait(&barrier->handle);

  js_value_t *success;
  err = js_get_boolean(env, err > 0, &success);
  assert(err == 0);

  return success;
}

static js_value_t *
bare_atomics_exports(js_env_t *env, js_value_t *exports) {
  int err;

#define V(name, fn) \
  { \
    js_value_t *val; \
    err = js_create_function(env, name, -1, fn, NULL, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V("mutexInit", bare_atomics_mutex_init)
  V("mutexDestroy", bare_atomics_mutex_destroy)
  V("mutexLock", bare_atomics_mutex_lock)
  V("mutexTryLock", bare_atomics_mutex_try_lock)
  V("mutexUnlock", bare_atomics_mutex_unlock)

  V("semaphoreInit", bare_atomics_semaphore_init)
  V("semaphoreDestroy", bare_atomics_semaphore_destroy)
  V("semaphoreWait", bare_atomics_semaphore_wait)
  V("semaphoreTryWait", bare_atomics_semaphore_try_wait)
  V("semaphorePost", bare_atomics_semaphore_post)

  V("conditionInit", bare_atomics_condition_init)
  V("conditionDestroy", bare_atomics_condition_destroy)
  V("conditionWait", bare_atomics_condition_wait)
  V("conditionSignal", bare_atomics_condition_signal)
  V("conditionBroadcast", bare_atomics_condition_broadcast)

  V("barrierInit", bare_atomics_barrier_init)
  V("barrierDestroy", bare_atomics_barrier_destroy)
  V("barrierWait", bare_atomics_barrier_wait)
#undef V

  return exports;
}

BARE_MODULE(bare_atomics, bare_atomics_exports)
