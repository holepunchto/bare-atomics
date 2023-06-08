#include <assert.h>
#include <bare.h>
#include <js.h>
#include <stdint.h>
#include <stdlib.h>
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
bare_atomics_mutex_init (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bool recursive;
  err = js_get_value_bool(env, argv[0], &recursive);
  assert(err == 0);

  bare_atomics_mutex_t *handle = malloc(sizeof(bare_atomics_mutex_t));

  if (recursive) {
    err = uv_mutex_init_recursive((uv_mutex_t *) handle);
  } else {
    err = uv_mutex_init((uv_mutex_t *) handle);
  }

  assert(err == 0);

  js_value_t *result;
  err = js_create_external(env, handle, NULL, NULL, &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_atomics_mutex_destroy (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_mutex_t *handle;
  err = js_get_value_external(env, argv[0], (void **) &handle);
  assert(err == 0);

  uv_mutex_destroy((uv_mutex_t *) handle);

  free(handle);

  return NULL;
}

static js_value_t *
bare_atomics_mutex_lock (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_mutex_t *handle;
  err = js_get_value_external(env, argv[0], (void **) &handle);
  assert(err == 0);

  uv_mutex_lock((uv_mutex_t *) handle);

  return NULL;
}

static js_value_t *
bare_atomics_mutex_try_lock (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_mutex_t *handle;
  err = js_get_value_external(env, argv[0], (void **) &handle);
  assert(err == 0);

  err = uv_mutex_trylock((uv_mutex_t *) handle);

  js_value_t *success;
  err = js_get_boolean(env, err == 0, &success);
  assert(err == 0);

  return success;
}

static js_value_t *
bare_atomics_mutex_unlock (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_mutex_t *handle;
  err = js_get_value_external(env, argv[0], (void **) &handle);
  assert(err == 0);

  uv_mutex_unlock((uv_mutex_t *) handle);

  return NULL;
}

static js_value_t *
bare_atomics_semaphore_init (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  uint32_t value;
  err = js_get_value_uint32(env, argv[0], &value);
  assert(err == 0);

  bare_atomics_semaphore_t *handle = malloc(sizeof(bare_atomics_semaphore_t));

  err = uv_sem_init((uv_sem_t *) handle, value);
  assert(err == 0);

  js_value_t *result;
  err = js_create_external(env, handle, NULL, NULL, &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_atomics_semaphore_destroy (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_semaphore_t *handle;
  err = js_get_value_external(env, argv[0], (void **) &handle);
  assert(err == 0);

  uv_sem_destroy((uv_sem_t *) handle);

  free(handle);

  return NULL;
}

static js_value_t *
bare_atomics_semaphore_wait (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_semaphore_t *handle;
  err = js_get_value_external(env, argv[0], (void **) &handle);
  assert(err == 0);

  uv_sem_wait((uv_sem_t *) handle);

  return NULL;
}

static js_value_t *
bare_atomics_semaphore_try_wait (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_semaphore_t *handle;
  err = js_get_value_external(env, argv[0], (void **) &handle);
  assert(err == 0);

  err = uv_sem_trywait((uv_sem_t *) handle);

  js_value_t *success;
  err = js_get_boolean(env, err == 0, &success);
  assert(err == 0);

  return success;
}

static js_value_t *
bare_atomics_semaphore_post (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_semaphore_t *handle;
  err = js_get_value_external(env, argv[0], (void **) &handle);
  assert(err == 0);

  uv_sem_post((uv_sem_t *) handle);

  return NULL;
}

static js_value_t *
bare_atomics_condition_init (js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_atomics_condition_t *handle = malloc(sizeof(bare_atomics_condition_t));

  err = uv_cond_init((uv_cond_t *) handle);
  assert(err == 0);

  js_value_t *result;
  err = js_create_external(env, handle, NULL, NULL, &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_atomics_condition_destroy (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_condition_t *handle;
  err = js_get_value_external(env, argv[0], (void **) &handle);
  assert(err == 0);

  uv_cond_destroy((uv_cond_t *) handle);

  free(handle);

  return NULL;
}

static js_value_t *
bare_atomics_condition_wait (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 3);

  bare_atomics_condition_t *handle;
  err = js_get_value_external(env, argv[0], (void **) &handle);
  assert(err == 0);

  bare_atomics_mutex_t *mutex;
  err = js_get_value_external(env, argv[1], (void **) &mutex);
  assert(err == 0);

  int64_t timeout;
  err = js_get_value_int64(env, argv[2], &timeout);
  assert(err == 0);

  js_value_t *success;

  if (timeout == -1) {
    uv_cond_wait((uv_cond_t *) handle, (uv_mutex_t *) mutex);

    err = js_get_boolean(env, true, &success);
    assert(err == 0);
  } else {
    err = uv_cond_timedwait((uv_cond_t *) handle, (uv_mutex_t *) mutex, timeout);

    err = js_get_boolean(env, err == 0, &success);
    assert(err == 0);
  }

  return success;
}

static js_value_t *
bare_atomics_condition_signal (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_condition_t *handle;
  err = js_get_value_external(env, argv[0], (void **) &handle);
  assert(err == 0);

  uv_cond_signal((uv_cond_t *) handle);

  return NULL;
}

static js_value_t *
bare_atomics_condition_broadcast (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_condition_t *handle;
  err = js_get_value_external(env, argv[0], (void **) &handle);
  assert(err == 0);

  uv_cond_broadcast((uv_cond_t *) handle);

  return NULL;
}

static js_value_t *
bare_atomics_barrier_init (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  uint32_t count;
  err = js_get_value_uint32(env, argv[0], &count);
  assert(err == 0);

  bare_atomics_barrier_t *handle = malloc(sizeof(bare_atomics_barrier_t));

  err = uv_barrier_init((uv_barrier_t *) handle, count);
  assert(err == 0);

  js_value_t *result;
  err = js_create_external(env, handle, NULL, NULL, &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_atomics_barrier_destroy (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_barrier_t *handle;
  err = js_get_value_external(env, argv[0], (void **) &handle);
  assert(err == 0);

  uv_barrier_destroy((uv_barrier_t *) handle);

  free(handle);

  return NULL;
}

static js_value_t *
bare_atomics_barrier_wait (js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  bare_atomics_barrier_t *handle;
  err = js_get_value_external(env, argv[0], (void **) &handle);
  assert(err == 0);

  err = uv_barrier_wait((uv_barrier_t *) handle);

  js_value_t *success;
  err = js_get_boolean(env, err > 0, &success);
  assert(err == 0);

  return success;
}

static js_value_t *
init (js_env_t *env, js_value_t *exports) {
#define V(name, fn) \
  { \
    js_value_t *val; \
    js_create_function(env, name, -1, fn, NULL, &val); \
    js_set_named_property(env, exports, name, val); \
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

BARE_MODULE(bare_atomics, init)
