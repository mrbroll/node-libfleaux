var assert = require('assert')
var fleaux = require('../index.js')

describe('Cursor', function() {
    describe('#insert()', function() {
        it('should insert the input string into the editor', function() {
            var editor = new fleaux.Editor()
            var cursor = new fleaux.Cursor(editor)

            cursor.insert('Hello, World!\n')
        })
    })
})
