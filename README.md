## json-cpp 轻量化解析器

作为轻量化解析器，目标是从 JSON 字符串中提取键值对、嵌套对象 (`{}`) 和数组 (`[]`)，同时维持层级和嵌套关系。实现递归解析格式规整的 JSON 字符串。

[项目地址: floraison-io/json-cpp: A minimal JSON parser](https://github.com/floraison-io/json-cpp)

支持：

* 嵌套 JSON 对象（多层花括号）

* 数组嵌套（数组中可以包含数组或对象）

* 字符串和基本类型

不支持：

* 处理转义字符，如 `\"`。

* 键值之间的语法校验，错误恢复。
