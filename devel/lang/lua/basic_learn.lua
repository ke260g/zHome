#!/usr/bin/lua
print("Hello World")

-- This is line comment

--[[
These is block comment0
These is block comment1
These is block comment2
--]]

--[[
only `nil` and `false` in bool type means False
number `0`, '\0' all mean True

Any declaration of variables without `local` means global
even though the variables declared in statement-blocks or functions

not-equal symbol use ~= in lua, instead of !=

No `++`, `+=`, `-=`
--]]



-- loop-syntax0, while-do-end
-- sum from 1 to 100
sum = 0
num = 1
while num <= 100 do
    sum = sum + num
    num = num + 1
end
print("sum =",sum)

-- loop-syntax1, for-do-end
-- sum of odd-number from 1 to 100
sum = 0
for i = 1, 100, 2 do
    sum = sum + i
end
print("sum =",sum)

-- loop-syntax2, repeat-util
sum = 2
repeat
   sum = sum ^ 2 --ÃÝ²Ù×÷
   print(sum)
until sum >1000

--[[ branch
if-then
if-then-else-end
if-then-elseif-then-end
--]]
if 1 then
print("Hello Boys")
end

if 0 then
print("Bye")
else
print("Hello Girls")
end

if 0 then
sum = 1
elseif 0 then
sum = 2
else
sum = 3
print(sum)
end

-- std IO
name = io.read()
io.write("Your name is", name, "Right ?")
print("too young, too naive!\n")


function newCounter()
    local i = 0
    return function()     -- anonymous function
       i = i + 1
        return i
    end
end

c1 = newCounter()
print(c1())
print(c1())

function myPower(x)
    return function(y) return y^x end
end
 
power2 = myPower(2)
power3 = myPower(3)

print(power2(4))
print(power3(5))

-- multi-variables assign
name, age, bGay = "haoel", 37, false, "haoel@hotmail.com"
-- fourth value will be discarded

-- multi-variables-returned function
function getUserInfo()
    return "haoel", 37, "haoel@hotmail.com", "http://jb51.net"
end
name, age, email, website, bGay = getUserInfo()
-- no variable return to the bGay, bGay will be nil

-- Table, a data-structure like struct in C
haoel = {name="ChenHao", age=37, handsome=True}
-- Table access
haoel.website="http://www.baidu.com/"
local age = haoel.age
haoel.handsome = false
haoel.name=nil
-- Table,
t = {[20]=100, ['name']="ChenHao", [3.14]="PI"}
t[20] = 2000
t["name"] = Orona
t[3.14] = "pi"

-- Table, array like
arr = {10,20,30,40,50}
arr = {[1]=10, [2]=20, [3]=30, [4]=40, [5]=50}
io.write("The lengthe of arr{} is ", #arr, "\n")
io.write("_G is the Table of all the global variables, _G.sum is ", _G.sum, "\n")
-- Table, whose suffix is begin from `1' but not the `0'

-- implement `2/3 + 4/7` with metatable
-- [1] implement the `+` MetaMethod in `fraction_op`-MetaTable
fraction_op={}
function fraction_op.__add(f1, f2)
    ret = {}
    ret.numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator
    ret.denominator = f1.denominator * f2.denominator
    return ret
end
-- [2] define variables
fraction_a = {numerator=2, denominator=3}
fraction_b = {numerator=4, denominator=7}
-- [3] set varitables to the `fraction_op`-MetaTable
setmetatable(fraction_a, fraction_op)
setmetatable(fraction_b, fraction_op)
-- [4] manipulate
fraction_s = fraction_a + fraction_b
-- [5] check the result
io.write("fraction_s is ", fraction_s.numerator, "/", fraction_s.denominator, "\n")

-- setmetatable() return the value of first-input-parameter
--[[ lua build-in MetaMethod
__add(a, b)                      a + b
__sub(a, b)                      a - b
__mul(a, b)                      a * b
__div(a, b)                      a / b
__mod(a, b)                      a % b
__pow(a, b)                      a ^ b
__unm(a)                         -a
__concat(a, b)                   a .. b
__len(a)                         #a
__eq(a, b)                       a == b
__lt(a, b)                       a < b
__le(a, b)                       a <= b
__index(a, b)                    a.b
__newindex(a, b, c)              a.b = c
__call(a, ...)                   a(...)
--]]

Window_Prototype = {x=0, y=0, width=100, height=100}
MyWin = {title="Hello"}
setmetatable(MyWin, {__index = Window_Prototype})
-- then, {x, y, width, height} can be accessed from MyWin
--[[
when the table want to access a key like `table[key]`,
Lua find the key from the table-self, if it can't be found
and the table has __index() MetaTable,
then Lua will find the key following the rules defined by __index()
--]]

Person={}
function Person:new(p)
    local obj = p
    if (obj == nil) then
        obj = {name="ChenHao", age=37, handsome=true}
    end
    self.__index = self
    return setmetatable(obj, self)
end

function Person:toString()
    return self.name .." : ".. self.age .." : ".. (self.handsome and "handsome" or "ugly")
end

me = Person:new()
print(me:toString())

kf = Person:new{name="King's fucking", age=70, handsome=false}
print(kf:toString())

Student = Person:new()
function Student:new()
    newObj = {year = 2013}
    self.__index = self
    return setmetatable(newObj, self)
end

function Student:toString()
    return "Student : ".. self.year.." : " .. self.name
end

-- 1£©self just means Person£¬Person:new(p) is equal to Person.new(self, p)
-- 2£©self.__index = self, is to avoid the __index being rewrited

-- need a file `model_name.lua`, like `import` in python
require("model_name") -- load and run once
dofile("model_name") -- load and run every-time
loadfile("model_name") -- load and never run
