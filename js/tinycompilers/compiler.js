const tokenizer = require('./tokenizer');
const parser = require('./parser');
const transformer = require('./transformer');
const generator = require('./code-generator');

function compiler(input) {
  let tokens = tokenizer(input);
  let ast = parser(tokens);
  let newAST = transformer(ast);
  return generator(newAST);
}
let input = '(add (sub (f 2) 1) 3)';
console.log(compiler(input));