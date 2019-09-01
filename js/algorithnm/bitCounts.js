/**
 * 计算[0, num]范围内的每一个数的二进制中1的个数
 * 思路：使用动态规划的思想，因为奇偶数的区别在于其最后一位是否是1，那么某个数如果是偶数，他1的个数
 * 等于其除以2后的数的1个数。
 * @param {number} num
 * @return {number[]}
 */
var countBits = function(num) {
    let arr = new Array(num+1);
    for (let i = 0; i < arr.length; i++) {
        arr[i] = 0;
        if (i % 2 == 0) {
            arr[i] = arr[i >> 1];
        } else {
            arr[i] = arr[i >> 1] + 1;
        }
    }
    return arr;
};

console.log(countBits(4))