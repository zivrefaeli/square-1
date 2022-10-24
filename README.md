# Square-1
A special variant of Rubik's Cube, built in C

## Demo
By displaying the following cube at the console
![square-1](/assets/model.jpeg)

The result is
```
       {Yellow, Orange} / {Yellow, Green, Orange}
{Yellow, Orange, Blue} / {Yellow, Green}
       {Yellow, Blue} / {Yellow, Red, Green}
 {Yellow, Blue, Red} / {Yellow, Red}

{1, Red} | {2, Red}

 {White, Red, Blue} \ {White, Red}
       {White, Blue} \ {White, Green, Red}
{White, Blue, Orange} \ {White, Green}
       {White, Orange} \ {White, Orange, Green}
```

(Image was taken from [Walmart](https://i5.walmartimages.com/asr/cf69bda5-e90f-4508-bb01-165ccb8c7fac.9214a75dc2105517d8beeb2d02ef2d6d.jpeg))

## Usage

There are 3 main methods to use in this project
```c
void print_cube(Cube *cube);

void slice(Cube *cube);

void rotate(Cube *cube, int top, int bottom);
```

<br />

For example, to impelemnt the <b>[Parity Algorithem](https://www.kungfoomanchu.com/guides/andy-klise-square-1.pdf)</b> of Square-1

```c
int moves[][2] = {
    {-3, 0}, {0, 3}, {0, -3}, {0, 3}, {2, 0}, {0, 2}, 
    {-2, 0}, {4, 0}, {0, -2}, {0, 2}, {-1, 4}, {0, -3}
};
int length = sizeof(moves) / sizeof(int[2]);

slice(square1);
for (int i = 0; i < length; i++) {
    rotate(square1, moves[i][0], moves[i][1]);
    slice(square1);
}
rotate(square1, 0, 3);

print_cube(square1);
```

## Licence
TODO