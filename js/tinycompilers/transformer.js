/**
 * 使用traveser将lisp形式的ast转换为c++形式的ast表达方式
 */
const traverser = require('./traverser');

function transformer(ast) {
  let newAST = {
    type: 'Program',
    body: [],
  };

  ast._ctx = newAST.body;
  traverser(ast, {
    NumberLiteral: {
      enter(node, parent) {
        parent._ctx.push({
          type: node.type,
          value: node.value
        });
      }
    },
    StringLiteral: {
      enter(node, parent) {
        parent._ctx.push({
          type: node.type,
          value: node.value,
        });
      }
    },
    CallExpression: {
      enter(node, parent) {
        // console.log(`transform: node.params: ${node.params}`)
        let expression = {
          type: node.type,
          callee: {
            type: 'Identifier',
            name: node.name
          },
          arguments: [],
        };

        node._ctx = expression.arguments;
        if (parent.type !== 'CallExpression') {
          expression = {
            type: 'ExpressionStatement',
            expression
          };
        }
        parent._ctx.push(expression);
      }
    }
  });
  return newAST;
}

module.exports = transformer;