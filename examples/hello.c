#include "reactor-uc/builtin_triggers.h"
#include "reactor-uc/environment.h"
#include "reactor-uc/reaction.h"
#include "reactor-uc/reactor.h"
#include <stdio.h>

typedef struct {
  Startup super;
  Reaction *effects_[1];
} MyStartup;

typedef struct {
  Reaction super;
} MyReaction;

typedef struct {
  Reactor super;
  MyReaction my_reaction;
  MyStartup startup;
  int cnt;
} MyReactor;

void MyStartup_ctor(MyStartup *self, Reactor *parent, Reaction *effects) {
  self->effects_[0] = effects;
  Startup_ctor(&self->super, parent, self->effects_, 1);
}

int startup_handler(Reaction *_self) {
  MyReactor *self = (MyReactor *)_self->parent;
  (void)self;
  printf("Hello World\n");
  return 0;
}

void MyReaction_ctor(MyReaction *self, Reactor *parent) {
  Reaction_ctor(&self->super, parent, startup_handler, NULL, 0);
}

void MyReactor_ctor(MyReactor *self, Environment *env) {
  Reactor_ctor(&self->super, env);
  MyReaction_ctor(&self->my_reaction, &self->super);
  MyStartup_ctor(&self->startup, &self->super, &self->my_reaction.super);
  self->super.register_startup(&self->super, &self->startup.super);
}

MyReactor my_reactor;
Reactor *reactors[] = {(Reactor *)&my_reactor};

int main() {
  Environment env;
  Environment_ctor(&env, reactors, 1);
  MyReactor_ctor(&my_reactor, &env);
  env.assemble(&env);
  env.start(&env);
}
