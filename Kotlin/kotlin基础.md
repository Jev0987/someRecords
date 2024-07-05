# 基础类型

| 类别 | 基础类型 |
| --- | --- |
| 整数型 | Byte, Short, Int, Long |
| 无符号整数 | UByte, UShort, UInt, ULong |
| 浮点数 | Float, Double |
| 字符 | Char |
| 字符串 | String |
| 布尔值 | Boolean |

# 容器

| 容器类型 | 描述 |
| --- | --- |
| Lists | 有序容器 |
| Sets | 无序不重复容器 |
| Maps | key-value 存储容器，key值不能重复 |

## Lists

创建容器

```kotlin
listof()  // 只读list
mutableListOf()  // 可变list
val xxx : MutableList<String> = mutableListOf(1,2,3,4)  // 显式指定类型List
val xxxLocked : List<String> = xxx   // 重新上锁
```

判断是否元素在list内

```kotlin
println(1 in xxx)  // true
```

添加和删除元素

```kotlin
xxx.add(5)
xxx.remove(2)
```

## Set

类似

## Map

注意key值不重复

使用to创建map

```kotlin
val readOnlyxxx = mapOf("a" to 1, "b" to 2, "c" to 3)  // 只读map

val xxx : MutableMap<String, Int> = mutableMapOf("a" to 1, "b" to 2, "c" to 3)  // 可修改map

val readOnlyxxx : Map<String, Int> = xxx

// {a=1,b=2,c=3}
```

插入和删除元素

```kotlin
xxx.put("d", 4)
xxx.remove("c")
```

是否包含

```kotlin
xxx.containsKey("a") // true
```

打印key或values

```kotlin
xxx.keys
xxx.values
```

# 函数

```kotlin
fun hello (x : String) {  // 普通
	 return println("hello $x")
}

fun sum(x : Int, y :Int) : Int {  // 带返回值
	return x + y
}

fun sum(x : Int, y : Int) = x + y  // single-expression function

```

## Lambda

```kotlin
fun main() {
	println({text : String -> text.uppercase() }("hello"))
}
```

text 是函数参数，类型是String

函数返回值为text.uppercase()

如果没有函数返回值，那就可以不需要→

```kotlin
{println("Log message")}
```

### 指派给变量

```kotlin
val upperCaseString = { text : String -> text.uppercase()}  // 利用变量接受lambda表达式
println(upperCaseString("hello"))
```

### lambda表达式在容器函数中的使用

```kotlin
val numbers = listOf(1, -2, 3, -4, 5, -6)
val positives = numbers.filter { x -> x > 0 }
val negatives = numbers.filter { x -> x < 0 }
println(positives)
// [1, 3, 5]
println(negatives)
// [-2, -4, -6]
```

filter() 函数允许接受lambda表达式

.map()

```kotlin
val numbers = listOf(1, -2, 3, -4, 5, -6)
val doubled = numbers.map { x -> x * 2 }
val tripled = numbers.map { x -> x * 3 }
println(doubled)
// [2, -4, 6, -8, 10, -12]
println(tripled)
// [3, -6, 9, -12, 15, -18]
```

map()函数接收lambda表达式作为转换函数，操控容器内的元素

### 函数类型

多数情况都需要显式声明你的函数类型

编译器需要函数类型，这样它们才能知道哪些是被允许的函数，哪些不是被允许的。

语法如下：

- 括号内写参数，使用逗号隔开
- 返回值类型写在 → 后

例如：

```kotlin
(String) -> String
(Int, Int) -> Int
```

再举一个例子

```kotlin
val upperCaseString : (String) -> String = {text -> text.uppercase() }
```

函数upperCaseString()的类型为：`(String) -> String`

### 从函数中返回lambda

例子中使用when选择返回的lambda表达式

```kotlin
fun toSeconds(time: String): (Int) -> Int = when (time) {
    "hour" -> { value -> value * 60 * 60 }
    "minute" -> { value -> value * 60 }
    "second" -> { value -> value }
    else -> { value -> value }
}

fun main() {
    val timesInMinutes = listOf(2, 10, 15, 1)
    val min2sec = toSeconds("minute")
    val totalTimeInSeconds = timesInMinutes.map(min2sec).sum()
    println("Total time is $totalTimeInSeconds secs")
    // Total time is 1680 secs
}
```

### 单独调用

通过在大括号后使用括号()包含参数来直接调用lambda函数

```kotlin
println({ text: String -> text.uppercase() }("hello"))
```

### 尾部调用lambda

```kotlin
// 初始值为0
// 将初始值和在list中的每个item值进行累加
println(listOf(1, 2, 3).fold(0, { x, item -> x + item })) // 6

// Alternatively, in the form of a trailing lambda
println(listOf(1, 2, 3).fold(0) { x, item -> x + item })  // 6
```

### 练习

```kotlin
// 将actions和prefix以及id组合起来
// 例如：https://example.com/book-info/5/title

fun main() {
	val actions = listOf("title", "year", "author")
	val prefix = "https://example.com/book-info"
	val id = 5
	val urls = actions.map{ x -> "$prefix/$id/$x"}
	println(urls)
}
// [https://example.com/book-info/5/title, https://example.com/book-info/5/year, https://example.com/book-info/5/author]
```

```kotlin
/**
	写一个函数，需要带Int和类型为：()->Uint的函数作为参数，重复这个函数类型参数5次
	使用这个函数打印Hello 5次
**/
fun repeatN(n: Int, action: () -> Unit) {
    // Write your code here
    for (i in 1..n) {
        action()
    }
}

fun main() {
    // Write your code here
    repeatN(5) {
        println("Hello")
    }
}
```

# 类

## 声明属性

```kotlin
class Contact (val id : Int, var email: String)

class Contact (val id : Int, var email: String) {
	val category: String = ""
}
```

## 创建类实例

```kotlin
class Contact(val id : Int, var email: String)

fun main() {
	val contact = Contact(1, "Jev@gmail.com")
}
```

## 成员函数

```kotlin
class Contact(val id: Int, var email: String) {
	fun printID() {
		println(id)
	}
}

fun main() {
	val contact = Contact(1, "Jev@gmail.com")
	contact.printId()
}
```

## 数据类 data classes

kotlin使用数据类存放数据。

数据类有附加的成员函数

这些成员允许你轻松打印实例的可读输出，对比实例以及复制实例。

声明一个数据类，使用关键词data

```kotlin
data class User(val name : String, val id : Int)
```

最常用的预定义成员函数有：

- toString()
- equals()
- copy()

## 练习

```kotlin
data class Employee(val name :String, var salary : Int)
fun main() {
    val emp = Employee("Mary", 20)
    println(emp)
    emp.salary += 10
    println(emp)
}
```

```kotlin
import kotlin.random.Random

data class Employee(val name: String, var salary: Int)

// Write your code here
class RandomEmployeeGenerator(var minSalary : Int, var maxSalary : Int) {
    val nameList = listOf("a", "b", "c", "d", "e", "f")
    
    fun generateEmployee() : Employee{
        val tmp = Employee(nameList.random(), Random.nextInt(minSalary, maxSalary))
    	return tmp
    }
}
fun main() {
    val empGen = RandomEmployeeGenerator(10, 30)
    println(empGen.generateEmployee())
    println(empGen.generateEmployee())
    println(empGen.generateEmployee())
    empGen.minSalary = 50
    empGen.maxSalary = 100
    println(empGen.generateEmployee())
}
```

# Null 安全

## 可空类型

默认是不可接收空类型

可空类型需要通过? 来显式声明

```kotlin
var neverNull : String = "no null"
neverNull = null  // error

val nullable : String? = "can null"
nullable = null  // ok
```

## 检查你的可空类型

使用if来检查

## 安全调用

在类对象中调用空类型，需要使用安全调用操作符?.

安全调用可以返回null

这可以有效避免错误发生

```kotlin
fun lengthString (maybeString : String?) : Int ? = maybeString?.length

fun main() {
	val nullString : String ?= null
	println(lengthString(nullString))
	//null
}
```

## 艾维斯操作符

?:

艾维斯操作符在左边，说明什么是需要被检测是否为null的

```kotlin
val nullString: String? = null
```

艾维斯操作符在右边，则如果为null返回对应值

```kotlin
println(nullString?.length ?: 0)  // 返回0
```

## 练习

```kotlin
data class Employee (val name: String, var salary: Int)

fun employeeById(id: Int) = when(id) {
    1 -> Employee("Mary", 20)
    2 -> null
    3 -> Employee("John", 21)
    4 -> Employee("Ann", 23)
    else -> null
}

fun salaryById(id: Int) = employeeById(id)?.salary ?: 0

fun main() {
    println((1..5).sumOf { id -> salaryById(id) })
}
```