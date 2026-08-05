# bare-atomics

Native synchronization primitives for JavaScript.

```
npm i bare-atomics
```

<!-- bare-refgen:api start -->

## API

### Mutex

#### `new Mutex(opts?: MutexOptions)`

**Parameters**

| Parameter | Type           | Default | Description                                                                                                                                           |
| --------- | -------------- | ------- | ----------------------------------------------------------------------------------------------------------------------------------------------------- |
| `opts?`   | `MutexOptions` | —       | Options; set `recursive: true` to let the owning thread lock the mutex more than once (default `false`). May also carry an existing `handle` to wrap. |

#### `Mutex.destroy(): void`

**Throws**

- The mutex is still held.

#### `Mutex.handle: SharedArrayBuffer`

A `SharedArrayBuffer` with the underlying mutex handle.

#### `held: boolean`

Whether or not the current thread currently holds the mutex.

#### `lock(): void`

**Throws**

- The mutex is already held and was not created with `recursive: true`.

#### `Mutex.from(handle: SharedArrayBuffer, opts?: MutexOptions): Mutex`

Create a `Mutex` from an existing `handle`; options are the same as `new Mutex()`.

**Parameters**

| Parameter | Type                | Default | Description                                                                    |
| --------- | ------------------- | ------- | ------------------------------------------------------------------------------ |
| `handle`  | `SharedArrayBuffer` | —       | A `SharedArrayBuffer` holding an existing mutex, as exposed by `Mutex.handle`. |
| `opts?`   | `MutexOptions`      | —       | Options, the same as `new Mutex()`.                                            |

**Returns** `Mutex` — A `Mutex` sharing the underlying `handle`.

#### `recursive: boolean`

#### `tryLock(): boolean`

**Throws**

- The mutex is already held and was not created with `recursive: true`.

#### `unlock(): void`

**Throws**

- The mutex is not currently held.

### Semaphore

#### `new Semaphore(value: any)`

**Parameters**

| Parameter | Type  | Default | Description                                        |
| --------- | ----- | ------- | -------------------------------------------------- |
| `value`   | `any` | —       | The initial value (permit count) of the semaphore. |

#### `Semaphore.destroy(): void`

**Throws**

- The mutex is still held.

#### `Semaphore.handle: SharedArrayBuffer`

A `SharedArrayBuffer` with the underlying mutex handle.

#### `post(): void`

#### `Semaphore.from(handle: SharedArrayBuffer): Semaphore`

**Parameters**

| Parameter | Type                | Default | Description                                                                            |
| --------- | ------------------- | ------- | -------------------------------------------------------------------------------------- |
| `handle`  | `SharedArrayBuffer` | —       | A `SharedArrayBuffer` holding an existing semaphore, as exposed by `Semaphore.handle`. |

**Returns** `Semaphore` — A `Semaphore` sharing the underlying `handle`.

#### `tryWait(): boolean`

#### `wait(): void`

**Throws**

- The associated mutex is not held by the current thread.

### Condition

#### `broadcast(): void`

#### `Condition.from(handle: SharedArrayBuffer): Condition`

**Parameters**

| Parameter | Type                | Default | Description                                                                                     |
| --------- | ------------------- | ------- | ----------------------------------------------------------------------------------------------- |
| `handle`  | `SharedArrayBuffer` | —       | A `SharedArrayBuffer` holding an existing condition variable, as exposed by `Condition.handle`. |

**Returns** `Condition` — A `Condition` sharing the underlying `handle`.

#### `Condition.destroy(): void`

#### `Condition.handle: SharedArrayBuffer`

A `SharedArrayBuffer` with the underlying mutex handle.

#### `signal(): void`

#### `Condition.wait(): boolean`

**Throws**

- The associated mutex is not held by the current thread.

### Barrier

#### `new Barrier(count: number)`

**Parameters**

| Parameter | Type     | Default | Description                                                                                              |
| --------- | -------- | ------- | -------------------------------------------------------------------------------------------------------- |
| `count`   | `number` | —       | The number of threads that must reach the barrier (call `wait()`) before they are all released together. |

#### `Barrier.from(handle: SharedArrayBuffer): Barrier`

**Parameters**

| Parameter | Type                | Default | Description                                                                        |
| --------- | ------------------- | ------- | ---------------------------------------------------------------------------------- |
| `handle`  | `SharedArrayBuffer` | —       | A `SharedArrayBuffer` holding an existing barrier, as exposed by `Barrier.handle`. |

**Returns** `Barrier` — A `Barrier` sharing the underlying `handle`.

#### `Barrier.destroy(): void`

#### `Barrier.handle: SharedArrayBuffer`

A `SharedArrayBuffer` with the underlying mutex handle.

#### `Barrier.wait(): boolean`

### Types

#### `MutexOptions`

```ts
interface MutexOptions {
  recursive?: boolean
}
```

<!-- bare-refgen:api end -->

## License

Apache-2.0
