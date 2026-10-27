const test = require('brittle')
const { Barrier } = require('..')
const Thread = require('bare-thread')

test('barrier', (t) => {
  const barrier = new Barrier(2)

  const thread = new Thread(require.resolve('./fixtures/barrier'), { data: barrier.handle })

  if (barrier.wait()) barrier.destroy()

  thread.join()

  t.pass()
})
