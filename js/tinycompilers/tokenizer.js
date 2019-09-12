/*
  将输入代码进行词法分析，将每个指定的字段变为token对象，这个对象包含type、value
*/
function tokenizer(input) {
  let current = 0; // 当前索引
  let tokens = [];
  let WHITESPACE = /\s/;
  let NUMBERS = /[0-9]/;
  let LETTERS = /[a-z]/i;

  while (current < input.length) {
    let char = input[current];

    if (char === '(') {
      tokens.push({
        type: 'paren',
        value: '('
      });
      current++;
    } else if (char === ')') {
      tokens.push({
        type: 'paren',
        value: ')'
      });
      current++;
    } else if (WHITESPACE.test(char)) {
      current++;
    } else if (NUMBERS.test(char)) {
      let value = '';
      while (NUMBERS.test(char)) {
        value += char;
        char = input[++current];
      }
      tokens.push({ type: 'number', value });
    } else if (char === '"') {
      let value = '';
      char = input[++current];
      while (char !== '"') {
        value += char;
        char = input[++current];
      }
      tokens.push({ type: 'string', value });
    } else if (LETTERS.test(char)) {
      let value = '';
      while (LETTERS.test(char)) {
        value += char;
        char = input[++current];
      }
      tokens.push({ type: 'name', value});
    } else {
      throw new TypeError(`Unknown token: ${char}`);
    }
  }
  return tokens;
}

module.exports = tokenizer;
