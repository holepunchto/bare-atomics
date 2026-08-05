interface MutexOptions {
  recursive?: boolean
}

export class Mutex {
  /**
   * @param opts - Options; set `recursive: true` to let the owning thread lock the mutex more than once (default `false`). May also carry an existing `handle` to wrap.
   */
  constructor(opts?: MutexOptions)

  /**
   * Create a `Mutex` from an existing `handle`; options are the same as `new Mutex()`.
   * @param handle - A `SharedArrayBuffer` holding an existing mutex, as exposed by `Mutex.handle`.
   * @param opts - Options, the same as `new Mutex()`.
   * @returns A `Mutex` sharing the underlying `handle`.
   */
  static from(handle: SharedArrayBuffer, opts?: MutexOptions): Mutex

  /** A `SharedArrayBuffer` with the underlying mutex handle. */
  handle: SharedArrayBuffer
  recursive: boolean
  /** Whether or not the current thread currently holds the mutex. */
  held: boolean

  /**
   * @throws The mutex is already held and was not created with `recursive: true`.
   */
  lock(): void
  /**
   * @throws The mutex is already held and was not created with `recursive: true`.
   */
  tryLock(): boolean
  /**
   * @throws The mutex is not currently held.
   */
  unlock(): void
  /**
   * @throws The mutex is still held.
   */
  destroy(): void
}

export class Semaphore {
  /**
   * @param value - The initial value (permit count) of the semaphore.
   */
  constructor(value: any)

  /**
   * @param handle - A `SharedArrayBuffer` holding an existing semaphore, as exposed by `Semaphore.handle`.
   * @returns A `Semaphore` sharing the underlying `handle`.
   */
  static from(handle: SharedArrayBuffer): Semaphore

  handle: SharedArrayBuffer

  /**
   * @throws The associated mutex is not held by the current thread.
   */
  wait(): void
  tryWait(): boolean
  post(): void
  /**
   * @throws The mutex is still held.
   */
  destroy(): void
}

export class Condition {
  /**
   * @param handle - A `SharedArrayBuffer` holding an existing condition variable, as exposed by `Condition.handle`.
   * @returns A `Condition` sharing the underlying `handle`.
   */
  static from(handle: SharedArrayBuffer): Condition

  handle: SharedArrayBuffer

  /**
   * @throws The associated mutex is not held by the current thread.
   */
  wait(): boolean
  signal(): void
  broadcast(): void
  destroy(): void
}

export class Barrier {
  /**
   * @param count - The number of threads that must reach the barrier (call `wait()`) before they are all released together.
   */
  constructor(count: number)

  /**
   * @param handle - A `SharedArrayBuffer` holding an existing barrier, as exposed by `Barrier.handle`.
   * @returns A `Barrier` sharing the underlying `handle`.
   */
  static from(handle: SharedArrayBuffer): Barrier

  handle: SharedArrayBuffer

  wait(): boolean
  destroy(): void
}
