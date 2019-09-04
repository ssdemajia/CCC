//https://www.codewars.com/kata/slow-looping/train/javascript
/**
 * Execute the loopBody function once for each item in the items array, 
 * waiting for the done function (which is passed into the loopBody function)
 * to be called before proceeding to the next item in the array.
 * @param {Array} items - The array of items to iterate through
 * @param {Function} loopBody - A function to execute on each item in the array.
 *		This function is passed 3 arguments - 
 *			1. The item in the current iteration,
 *			2. The index of the item in the array,
 *			3. A function to be called when the iteration may continue.
 * @returns {Promise} - A promise that is resolved when all the items in the 
 *		in the array have been iterated through.
 */
function slowLoop(items, loopBody) {
  function call(i) {
    if (i >= items.length) return;
    return new Promise((resolve, reject) => {
      loopBody(items[i], i, resolve);
    }).then(_ => {
      return call(i+1)
    })
  }
  return new Promise((resolve, reject) => {
    call(0).then(_ => resolve())
  })
}

let timer = (time, i, res) => setTimeout(_ => res(time), time);

let now = +new Date;
slowLoop([200, 200, 300, 400], timer).then(_ => {
  console.log(+new Date - now);
})