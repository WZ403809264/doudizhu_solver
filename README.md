# doudizhu_solver 斗地主残局解题器

This program is used to solve the problem of the endgame of doudizhu. 此程序是用来解决斗地主残局的。

## help 帮助

Enter the cards of the first hand and the second hand respectively. 分别输入先手方和后手方的牌。

Among them, 3-9, Jack, Queen, King, Ace and 2 are input normally, 10 is input 0, black joker is input Y, and red joker is input Z. 其中，3-9、J、Q、K、A、2正常输入，10输入0，小王输入Y，大王输入Z。

The number of points shall be in the order of maximum to minimum. 输入时按点数大到小顺序。

After the cards of both sides are input, enter the number of ban moves (if there is no ban moves, enter 0), and then enter the ban moves. 当双方的牌输入以后，输入禁手个数（没有则输入0），再输入禁手。

Ban moves include three belts and one (31), three belts and a pair (32), four belts and two (421), and four belts and two pairs (422). 禁手包括：三带一（31）、三带二（32）、四带二张（421）、四带二对（422）。

The calculation starts after all the above entries are completed. 以上均输入完成后开始计算。

## Operation effect 运行效果

先手方：2222101076543333

后手方：大王小王JJ999

禁手：三带二

程序输入：22220076543333回车ZYJJ999回车1回车32回车

offensive：2222101076543333

defensive：redjokerblackjokerJJ999

ban moves：three belts and a pair

program input：22220076543333\nZYJJ999\n1\n32\n

As shown in the figure below. 如下图所示。

![](https://i.postimg.cc/NGRVzqkv/image.png)

The output is shown in the figure below. 输出如下图所示。

![](https://i.postimg.cc/9fVzyjbX/image.png)
