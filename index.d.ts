interface MutexOptions {
  recursive?: boolean
}

export class Mutex {
  constructor(opts?: MutexOptions)

  static from(handle: SharedArrayBuffer, opts?: MutexOptions): Mutex

  handle: SharedArrayBuffer
  recursive: boolean
  held: boolean

  lock(): void
  tryLock(): boolean
  unlock(): void
  destroy(): void
}

export class Semaphore {
  constructor(value: any)

  static from(handle: SharedArrayBuffer): Semaphore

  handle: SharedArrayBuffer

  wait(): void
  tryWait(): boolean
  post(): void
  destroy(): void
}

export class Condition {
  static from(handle: SharedArrayBuffer): Condition

  handle: SharedArrayBuffer

  wait(): boolean
  signal(): void
  broadcast(): void
  destroy(): void
}

export class Barrier {
  constructor(count: number)

  static from(handle: SharedArrayBuffer): Barrier

  handle: SharedArrayBuffer

  wait(): boolean
  destroy(): void
}
