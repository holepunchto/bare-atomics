#include <assert.h>
#include <bare.h>
#include <js.h>
#include <uv.h>

static js_value_t *
init (js_env_t *env, js_value_t *exports) {
  return exports;
}

BARE_MODULE(bare_atomics, init)
