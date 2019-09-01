function curry(fn, ...args) {
    if (args.length == fn.length) {
        return fn(...args);
    }
    return function (...otherArgs) {
        return curry(fn, ...args, ...otherArgs);
    };
}

// test
(function() {
    function add(a, b, c) {
        return a+b+c;
    }
    const cadd = curry(add);
    console.log(cadd(1, 2)(3) === 6)
    console.log(cadd(3)(2)(3) === 8)
})();

function curryAdd(...args) {
    let result = args;
    function inner(...otherArgs) {
        result = result.concat(otherArgs);
        if (result.length == 3) {
            return result.reduce((prev, cur) => prev+cur, 0);
        }
        return inner
    }
    return inner
}

(function() {
    console.log(curryAdd(1, 2)(3))
    console.log(curryAdd(1)(2)(3))
})()