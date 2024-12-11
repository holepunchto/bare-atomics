const binding = require('./binding')

exports.Mutex = class Mutex {
  constructor(opts = {}) {
    const { recursive = false, handle = binding.mutexInit(recursive) } = opts

    this.handle = handle
    this.recursive = recursive
    this.held = false
  }

  lock() {
    if (this.held && !this.recursive)
      throw new Error('cannot relock already held mutex')

    binding.mutexLock(this.handle)

    this.held = true
  }

  tryLock() {
    if (this.held && !this.recursive)
      throw new Error('cannot relock already held mutex')

    return binding.mutexTryLock(this.handle)
  }

  unlock() {
    if (!this.held) throw new Error('cannot unlock unheld mutex')

    binding.mutexUnlock(this.handle)

    this.held = false
  }

  destroy() {
    if (this.held) throw new Error('cannot destroy held mutex')

    binding.mutexDestroy(this.handle)
  }

  static from(handle, opts = {}) {
    return new Mutex({ ...opts, handle })
  }
}

exports.Semaphore = class Semaphore {
  constructor(value, opts = {}) {
    if (typeof value === 'object') {
      opts = value
      value = 0
    }

    const { handle = binding.semaphoreInit(value) } = opts

    this.handle = handle
  }

  wait() {
    binding.semaphoreWait(this.handle)
  }

  tryWait() {
    return binding.semaphoreTryWait(this.handle)
  }

  post() {
    binding.semaphorePost(this.handle)
  }

  destroy() {
    binding.semaphoreDestroy(this.handle)
  }

  static from(handle, opts = {}) {
    return new Semaphore({ ...opts, handle })
  }
}

exports.Condition = class Condition {
  constructor(opts = {}) {
    const { handle = binding.conditionInit() } = opts

    this.handle = handle
  }

  wait(mutex, timeout = -1) {
    if (!mutex.held) throw new Error('cannot wait with unheld mutex')

    return binding.conditionWait(this.handle, mutex.handle, timeout)
  }

  signal() {
    binding.conditionSignal(this.handle)
  }

  broadcast() {
    binding.conditionBroadcast(this.handle)
  }

  destroy() {
    binding.conditionDestroy(this.handle)
  }

  static from(handle, opts = {}) {
    return new Condition({ ...opts, handle })
  }
}

exports.Barrier = class Barrier {
  constructor(count, opts = {}) {
    if (typeof count === 'object') {
      opts = count
      count = 0
    }

    const { handle = binding.barrierInit(count) } = opts

    this.handle = handle
  }

  wait() {
    return binding.barrierWait(this.handle)
  }

  destroy() {
    binding.barrierDestroy(this.handle)
  }

  static from(handle, opts = {}) {
    return new Barrier({ ...opts, handle })
  }
}
