function kmp(from, target) {
    if (target.length == 0) return 0;
    if (from.length == 0) return -1;
    
    function makeTable(target) {
        /**
         * 计算前后缀表，比如abcab的最长前后缀就是ab和ab，即前缀和后缀最长的交集
         */
        let table = new Array();
        let prefix = -1;
        let index = 0; // 指向当前子字符串
        table.push(-1);// 哨兵
        while (index < target.length) {
            console.log(prefix, index)
            if (prefix == -1 || target[prefix] == target[index]) {
                index++;
                prefix++;
                table.push(prefix);
            } else {
                prefix = table[prefix];
            }
        }
        return table;
    }
    let table = makeTable(target);
    let index = 0; // 指向from
    let t = 0; // 指向匹配对象 target
    while (index < from.length && t < target.length) {
        if (from[index] == target[t]) {
            index++;
            t++;
            if (t == target.length) {
                return index - target.length;
            }
        } else {
            if (table[t] == -1) {
                t = 0;
                index += 1;
            } else {
                t = table[t];
            }
        }
    }
    console.log(makeTable(target));
    return -1;
}

// "aabaaabaaac" "aabaaac"
console.log(kmp('hellowxcs', 'llow'));