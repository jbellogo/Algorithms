/**
 * @param {Function} fn
 * @return {Function}
 */
function memoize(fn) {
    let memoizations = {};  // {arg : cached_val}, { 1: 1, 2: 1, 3: 2, 4: 3, 5: 5, ... x: fib(x),...}

    function get_key(args_lst){
        // By sorting the list of arguments we can memoize any list of arguments up to permutations 
        // ie 3+1 and 1+3 only call once. I think this is better but LeetCode doesn;t want me to assume commutativity of operations, so just remove the sorting in submission
        args_lst.sort();
        let str = "";
        for (let i =0; i < args_lst.length; i++){
            str+=String(args_lst[i]);
            str+=" ";
        }
        return str;
    }

    return function(...args) {
        let key = get_key(args);
        console.log(`key: ${key}, args: ${args}`);
        if (!(key in memoizations)){ 
            // if fn(...args) has not been cached
            memoizations[key] = fn(...args);
            console.log("adding new memoization!");
        }
        return memoizations[key];
    }

}



/** 
 * let callCount = 0;
 * const memoizedFn = memoize(function (a, b) {
 *	 callCount += 1;
 *   return a + b;
 * })
 * memoizedFn(2, 3) // 5
 * memoizedFn(2, 3) // 5
 * console.log(callCount) // 1 
 */