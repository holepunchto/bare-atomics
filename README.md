# bare-atomics

Native synchronization primitives for JavaScript.

```
npm i bare-atomics
```

## API

### Mutex

#### `const mutex = new Mutex([options])`

Options include:

```js
{
  recursive: false
}
```

#### `const mutex = Mutex.from(handle[, options])`

Options are the same as `new Mutex()`.

#### `mutex.handle`

An `External` with a pointer to the underlying mutex handle.

#### `mutex.held`

Whether or not the current thread currently holds the mutex.

#### `mutex.lock()`

#### `const success = mutex.tryLock()`

#### `mutex.unlock()`

#### `mutex.destroy()`

### Semaphore

#### `const semaphore = new Semaphore(value)`

#### `const semaphore = Semaphore.from(handle)`

#### `semaphore.handle`

An `External` with a pointer to the underlying semaphore handle.

#### `semaphore.wait()`

#### `const success = semaphore.tryWait()`

#### `semaphore.post()`

#### `semaphore.destroy()`

### Condition

#### `const condition = new Condition()`

#### `const condition = Condition.from(handle)`

#### `condition.handle`

An `External` with a pointer to the underlying condition handle.

#### `const success = condition.wait(mutex[, timeout])`

#### `condition.signal()`

#### `condition.broadcast()`

#### `condition.destroy()`

### Barrier

#### `const barrier = new Barrier(count)`

#### `const barrier = Barrier.from(handle)`

#### `barrier.handle`

An `External` with a pointer to the underlying barrier handle.

#### `const success = barrier.wait()`

#### `barrier.destroy()`

## License

Apache-2.0
