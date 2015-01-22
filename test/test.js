var assert = require('chai').assert
var fleaux = require('../index.js')
var fs = require('fs')

describe('Editor Cursor Tests', function() {
    var ed;
    var curs;
    beforeEach(function() {
        ed = new fleaux.Editor()
        curs = new fleaux.Cursor(ed)
    })
    describe('Insertion Test', function() {
        it('Simple insert test', function() {
            var expected = fs.readFileSync('test/editor/insert_test_result.txt', 'utf8')
            curs.insert('this is the first line\n')
            curs.insert('this is the second line\n')
            curs.insert('this is the third line\nthis is the fourth line\nthis is the fifth line\n')
            var actual = ed.toString()
            assert(expected == actual, 'Insert test failed!!!')
        })
    })
    describe('Removal Test', function() {
        it('Simple remove test', function() {
            var expected = fs.readFileSync('test/editor/remove_test_result.txt', 'utf8')
            var input = fs.readFileSync('test/editor/remove_test_input.txt', 'utf8')
            curs.insert(input)
            curs.remove(-23)
            var actual = ed.toString()
            assert(expected == actual, 'Remove test failed!!!')
        })
    })
    describe('Move Test', function() {
        it('Exhaustive move, remove, insert, replace test', function() {
            var expected = fs.readFileSync('test/editor/move_test_result.txt', 'utf8')
            var input = fs.readFileSync('test/editor/move_test_input.txt', 'utf8')
            var cursor = curs
            cursor.insert(input)
            cursor.remove(-2)
            cursor.insert('.\n')
            cursor.moveY(-1)
            for (var i = 0; i < 5; i++) {
                cursor.moveY(-1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.moveX(-1)
            }
            cursor.remove(6)
            cursor.insert('......')
            cursor.moveX(-1)
            for (var i = 0; i < 2; i++) {
                cursor.moveY(-1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.moveX(-1)
            }
            for (var i = 0; i < 4; i++) {
                cursor.remove(-1)
                cursor.insert('.')
                cursor.moveX(-1)
                cursor.moveY(-1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.moveX(-1)
            }
            for (var i = 0; i < 4; i++) {
                cursor.moveX(1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.moveX(-1)
                cursor.moveY(-1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.moveX(-1)
            }
            cursor.remove(6)
            cursor.insert('......')
            cursor.moveX(-1)
            for (var i = 0; i < 2; i++) {
                cursor.moveY(1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.moveX(-1)
            }
            cursor.remove(4)
            cursor.insert('....')
            cursor.moveX(-1)
            for (var i = 0; i < 3; i++) {
                cursor.moveY(-1)
                cursor.moveX(1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.moveX(-1)
            }
            for (var i = 0; i < 10; i++) {
                cursor.moveY(-1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.moveX(-1)
            }
            cursor.remove(-4)
            cursor.insert('....')
            cursor.moveX(-4)
            for (var i = 0; i < 8; i++) {
                cursor.moveY(1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.moveX(-1)
            }
            cursor.remove(-12)
            cursor.insert('............')
            cursor.moveX(-12)
            for (var i = 0; i < 2; i++) {
                cursor.moveY(-1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.moveX(-1)
            }
            cursor.remove(10)
            cursor.insert('..........')
            cursor.moveX(-1)
            for (var i = 0; i < 8; i++) {
                cursor.moveY(-1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.moveX(-1)
            }
            cursor.remove(-3)
            cursor.insert('...')
            cursor.moveX(-3)
            for (var i = 0; i < 2; i++) {
                cursor.moveY(1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.moveX(-1)
                cursor.remove(-1)
                cursor.insert('.')
                cursor.moveX(-1)
            }
            for (var i = 0; i < 2; i++) {
                cursor.moveY(1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.moveX(-1)
            }
            cursor.remove(-4)
            cursor.insert('....')
            cursor.moveX(-4)
            for (var i = 0; i < 4; i++) {
                cursor.moveY(-1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.moveX(-1)
            }
            /* reverse */
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* down 4   */
            cursor.moveY(4)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* right 4  */
            cursor.moveX(4)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* up 2     */
            cursor.moveY(-2)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* 2x {     */
                /* right 1 */
                /* up 1    */
            /* }        */
            cursor.moveX(2)
            cursor.moveY(-2)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* right 3 */
            cursor.moveX(3)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* down 8 */
            cursor.moveY(8)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* left 9 */
            cursor.moveX(-9)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* down 2 */
            cursor.moveY(2)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* right 12 */
            cursor.moveX(12)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* up 8 */
            cursor.moveY(-8)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* right 4 */
            cursor.moveX(4)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* down 10 */
            cursor.moveY(10)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* down-left 3 */
            cursor.moveX(-3)
            cursor.moveY(3)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* left 3 */
            cursor.moveX(-3)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* up 2 */
            cursor.moveY(-2)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* left 5 */
            cursor.moveX(-5)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* 4x {     */
                /* down 1   */
                /* left 1   */
            /* }        */
            /* 4x {     */
                /* down 1   */
                /* right 1   */
            /* }        */
            cursor.moveY(8)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* down 2   */
            cursor.moveY(2)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* left 5   */
            cursor.moveX(-5)
            cursor.replace(1, '*')
            cursor.moveX(-1)
            /* down 5   */
            cursor.moveY(5)
            cursor.replace(1, '*')

            var actual = ed.toString()
            assert(expected == actual, 'Move test failed!!!')
        })
    })
})
