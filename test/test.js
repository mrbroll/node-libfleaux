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
            cursor.move(0, -1)
            for (var i = 0; i < 5; i++) {
                cursor.move(0, -1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.move(-1, 0)
            }
            cursor.remove(6)
            cursor.insert('......')
            cursor.move(-1, 0)
            for (var i = 0; i < 2; i++) {
                cursor.move(0, -1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.move(-1, 0)
            }
            for (var i = 0; i < 4; i++) {
                cursor.remove(-1)
                cursor.insert('.')
                cursor.move(-1, 0)
                cursor.move(0, -1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.move(-1, 0)
            }
            for (var i = 0; i < 4; i++) {
                cursor.move(1, 0)
                cursor.remove(1)
                cursor.insert('.')
                cursor.move(-1, 0)
                cursor.move(0, -1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.move(-1, 0)
            }
            cursor.remove(6)
            cursor.insert('......')
            cursor.move(-1, 0)
            for (var i = 0; i < 2; i++) {
                cursor.move(0, 1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.move(-1, 0)
            }
            cursor.remove(4)
            cursor.insert('....')
            cursor.move(-1, 0)
            for (var i = 0; i < 3; i++) {
                cursor.move(0, -1)
                cursor.move(1, 0)
                cursor.remove(1)
                cursor.insert('.')
                cursor.move(-1, 0)
            }
            for (var i = 0; i < 10; i++) {
                cursor.move(0, -1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.move(-1, 0)
            }
            cursor.remove(-4)
            cursor.insert('....')
            cursor.move(-4, 0)
            for (var i = 0; i < 8; i++) {
                cursor.move(0, 1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.move(-1, 0)
            }
            cursor.remove(-12)
            cursor.insert('............')
            cursor.move(-12, 0)
            for (var i = 0; i < 2; i++) {
                cursor.move(0, -1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.move(-1, 0)
            }
            cursor.remove(10)
            cursor.insert('..........')
            cursor.move(-1, 0)
            for (var i = 0; i < 8; i++) {
                cursor.move(0, -1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.move(-1, 0)
            }
            cursor.remove(-3)
            cursor.insert('...')
            cursor.move(-3, 0)
            for (var i = 0; i < 2; i++) {
                cursor.move(0, 1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.move(-1, 0)
                cursor.remove(-1)
                cursor.insert('.')
                cursor.move(-1, 0)
            }
            for (var i = 0; i < 2; i++) {
                cursor.move(0, 1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.move(-1, 0)
            }
            cursor.remove(-4)
            cursor.insert('....')
            cursor.move(-4, 0)
            for (var i = 0; i < 4; i++) {
                cursor.move(0, -1)
                cursor.remove(1)
                cursor.insert('.')
                cursor.move(-1, 0)
            }
            /* reverse */
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* down 4   */
            cursor.move(0, 4)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* right 4  */
            cursor.move(4, 0)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* up 2     */
            cursor.move(0, -2)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* 2x {     */
                /* right 1 */
                /* up 1    */
            /* }        */
            cursor.move(2, 0)
            cursor.move(0, -2)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* right 3 */
            cursor.move(3, 0)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* down 8 */
            cursor.move(0, 8)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* left 9 */
            cursor.move(-9, 0)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* down 2 */
            cursor.move(0, 2)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* right 12 */
            cursor.move(12, 0)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* up 8 */
            cursor.move(0, -8)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* right 4 */
            cursor.move(4, 0)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* down 10 */
            cursor.move(0, 10)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* down-left 3 */
            cursor.move(-3, 0)
            cursor.move(0, 3)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* left 3 */
            cursor.move(-3, 0)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* up 2 */
            cursor.move(0, -2)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* left 5 */
            cursor.move(-5, 0)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* 4x {     */
                /* down 1   */
                /* left 1   */
            /* }        */
            /* 4x {     */
                /* down 1   */
                /* right 1   */
            /* }        */
            cursor.move(0, 8)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* down 2   */
            cursor.move(0, 2)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* left 5   */
            cursor.move(-5, 0)
            cursor.replace(1, '*')
            cursor.move(-1, 0)
            /* down 5   */
            cursor.move(0, 5)
            cursor.replace(1, '*')

            var actual = ed.toString()
            assert(expected == actual, 'Move test failed!!!')
        })
    })
})
