
#include <stdio.h>
#include <pthread.h>

#include "sender/sender.h"
#include "receiver/receiver.h"
#include <machine/rtc.h>

static void* receiver_thread(void* arg) {
    (void)arg;
    lf_start_receiver();
    return NULL;
}

static void* sender_thread(void* arg) {
    (void)arg;
    lf_start_sender();
    return NULL;
}

int main(void) {
    pthread_t receiver_tid;
    pthread_t sender_tid;
    long long cycles_before = get_cpu_cycles();
    printf("Starting S4NOC Federated Example\n");

    pthread_create(&receiver_tid, NULL, receiver_thread, NULL);
    pthread_create(&sender_tid, NULL, sender_thread, NULL);

    printf("Federate threads started.\n");

    pthread_join(receiver_tid, NULL);
    pthread_join(sender_tid, NULL);

    long long cycles_after = get_cpu_cycles();
    printf("Total CPU cycles: %lld\n", cycles_after - cycles_before);
    return 0;
}
