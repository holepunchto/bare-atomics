const binding = require('./binding')

exports.Mutex = class Mutex {
  constructor (opts = {}) {
    const {
      recursive = false,
      handle = binding.mutexInit(recursive)
    } = opts

    this.handle = handle
    this.recursive = recursive
    this.held = false
  }

  lock () {
    if (this.held && !this.recursive) throw new Error('cannot relock already held mutex')

    binding.mutexLock(this.handle)

    this.held = true
  }

  tryLock () {
    if (this.held && !this.recursive) throw new Error('cannot relock already held mutex')

    binding.mutexTryLock(this.handle)
  }

  unlock () {
    if (!this.held) throw new Error('cannot unlock unheld mutex')

    binding.mutexUnlock(this.handle)

    this.held = false
  }

  destroy () {
    binding.mutexDestroy(this.handle)
  }

  static from (handle, opts = {}) {
    return new Mutex({ ...opts, handle })
  }
}

exports.Semaphore = class Semaphore {
  constructor (value, opts = {}) {
    if (typeof value === 'object') {
      opts = value
      value = 0
    }

    const {
      handle = binding.semaphoreInit(value)
    } = opts

    this.handle = handle
  }

  wait () {
    binding.semaphoreWait(this.handle)
  }

  tryWait () {
    return binding.semaphoreTryWait(this.handle)
  }

  post () {
    binding.semaphorePost(this.handle)
  }

  destroy () {
    binding.semaphoreDestroy(this.handle)
  }

  static from (handle, opts = {}) {
    return new Semaphore({ ...opts, handle })
  }
}
