# compiler
## **Grammar**

* **S**->**function** **C**
* **C**->**S**| $\epsilon$
* **function**->*type* *identifier* *(* **argument_list** *)* *{* **code_block** *}*
* **argument_list**->*type* *identifier* **_argument_list**| $\epsilon$
* **argument_list**->*,* *identifier* **_argument_list** | $\epsilon$
* **code_block**->**sentence** *;* **code_block**|**for_expr** **code_block**|**while_expr** **code_block**|** if_expr** **code_block**|**ret** *;* **code_block**|*break* **code_block** | *continue* **code_block** | *{* **code_block** *}* **code_block** 
* **sentence**->**expr** | **statement** | $\epsilon$
* **statement**->*type* *identifier* **equal** **X**
* **equal** -> *=* **expr**| $\epsilon$
* **X**->*,* *identifier* **equal** **X** | $\epsilon$
* **expr**->**A**
* **A**->**B** **A'**
* **A'**->*+* **B** **A'** | $\epsilon$
* ...
* **M**->*(* **A** *)* | *NUM* | **iden_or_func**
* **iden_or_func**->*identifier* *(**real_argument_list** *)* | *identifier*
* **real_argument_list**->**expr** **_real_argument_lst** | $\epsilon$
* **_real_argument_list**->*,* **expr** **_real_argument_list** | $\epsilon$
* **for_expr**->*for* *(* **sentence** *;* **expr** *;* **expr** | $\epsilon$ *)* *{* **code_block** *)*
* **while_expr** -> *while* *(* **expr** *)* *{* **code_block** *}*
* **if_expr** -> *if* *(* **expr** *)* *{* **code_block** *}*  | *if* *(* **expr** *)* *{* **code_block** *}* *else* **if_expr** | *if* *(* **expr** *)* *{* **code_block** *}* *else* *{* **code_block** *}*
* **ret** -> *return * **expr** | *return* 


## 解释器
#### 寄存器的说明
* %num 表示存的是临时变量
* %a 表示存的是函数返回值
* %j 表达式计算出的用来判断真假的值

#### 需要的指针
* sp 栈指针 (sp) 表示  * sp
* bp 基指针
* pc 指令指针　可以将所有指令存在一个string数组里 

#### 四元式的解释
* op a b c -> c = a op b
* = a b -> a = b
* push sp += 8
* pop sp -= 8
* add a
		std::unordered_map<std::string,std::vector<void*>> map;//这种数据结构
        void * p =(void * )sp;
        map[a].push_back(p);
        while(map[a].size()&&map[a][map[a].size()-1]>=sp) map[a].pop_back();
* jt num
		if(%j) pc = num;
* jf num
		if(!%j) pc = num;
       
---
>我会将 call lea add等指令拆成更基本的指令

>注意　每次执行完毕后 pc+=1