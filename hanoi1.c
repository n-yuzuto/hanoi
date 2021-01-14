#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define N_TOWER 3

unsigned *tower[N_TOWER];
unsigned *top[N_TOWER];
unsigned n_input;
unsigned n_steps = 0;

void print_tower(unsigned i) {
  assert(0 <= i && i < N_TOWER);
  unsigned *p = tower[i];

  printf("%d|", i);
  while (p != top[i]) {
    printf("%d]", *p);
    p++;
  }
  printf("\n");
}

void print_towers() {
  int i;
  for (i = 0; i < N_TOWER; i++) {
    print_tower(i);
  }
}

void move(unsigned from, unsigned to) {
  printf("### move %d to %d\n", from, to);
  // ここに処理を追加する。
  // define 
  unsigned *pointer=tower[from];
  while (pointer!=top[from]){
    ++pointer;
  }
  // look array
  *top[from]=0;
  *top[to]=*(pointer-1);
  --top[from];
  ++top[to];
  print_towers();
  n_steps++;
}



int verify_towers(unsigned i, unsigned *t0, unsigned *t1, unsigned *t2) {
  // ここに処理を追加する。関数の引数を変更しても良い。
  unsigned check_ring = 0;

  // roup
  while(t0!=top[0]){
    if(*t0==i){
      ++check_ring;
    }
    if(t0+1!=top[0]){
      if(*t0<*(t0+1)){
        return 0;
      }
    }
    t0++;
  }


  while(t1!=top[1]){
    if(*t1==i){
      ++check_ring;
    }
    if(t1+1!=top[1]){
      if(*t1<*(t1+1)){
        return 0;
      }
    }
    t1++;
  }


  while(t2!=top[2]){
    if(*t2==i){
      ++check_ring;
    }
    if(t2+1!=top[2]){
      if(*t2<*(t2+1)){
        return 0;
      }
    }
    t2++;
  }


  if(check_ring!=1){
    return 0;
  }    
  // call function
  if(i>1){
    verify_towers(i-1,tower[0],tower[1],tower[2]);
  }

  // check all things and return
  else if(i==0){
    if(t0!=top[0]){
      return 0;
    }
    if(t1!=top[1]){
      return 0;
    }
    if(t2!=top[2]){
      return 0;
    }
    else{
      return 1;
    }
  }
}



void hanoi(unsigned n, unsigned cur_pos, unsigned dest_pos) {
  assert(0 < n);
  assert(0 <= cur_pos && cur_pos < N_TOWER);
  assert(0 <= dest_pos && dest_pos < N_TOWER);

  // ここに処理を追加する。円盤を移動させる場合は move 関数を使うこと。
  // define
  unsigned else_space;
  int N;

  //roup
  for(N=0;N<N_TOWER;N++){
    if(N!=cur_pos){
        if(N!=dest_pos){
        else_space=N;
      }
    }
  }
  //call function
  if(n>1){
    hanoi(n-1,cur_pos,else_space);
  }
  move(cur_pos,dest_pos);
  if(n>1){
    hanoi(n-1,else_space,dest_pos);
  }
  if (verify_towers(n,tower[0],tower[1],tower[2])){
    puts("### verify: OK");
  } else {
    puts("### verify: FAILED");
    print_towers();
    exit(EXIT_FAILURE);
  }
}

int main(int argc ,char **argv) {
  int  i;

  assert(argc == 2);
  n_input = atoi(argv[1]);
  assert(n_input > 0);

  for (i = 0; i < N_TOWER; i++) {
    tower[i] = malloc(n_input * sizeof(unsigned));
    if (tower[i] == NULL) exit(EXIT_FAILURE);
    top[i] = tower[i];
  }
  for (i = 0; i < n_input; i++) {
    *top[0] = n_input - i;
    top[0]++;
  }

  puts("### start");
  print_towers();
  hanoi(n_input, 0, 2);
  printf("### %d steps to complete\n", n_steps);

  return 0;
}