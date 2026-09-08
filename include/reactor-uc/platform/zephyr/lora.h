#ifndef LORA_CHANNEL_H
#define LORA_CHANNEL_H

#include "reactor-uc/network_channel.h"
#include "reactor-uc/serialization.h"
#include <zephyr/kernel.h>
#include <zephyr/drivers/lora.h>
#include <stdint.h>
#include <stdbool.h>

#define LORA_CHANNEL_BUFFERSIZE 247
#define NETWORK_CHANNEL_TYPE_LORA 0x05

typedef struct LoRaPollChannel LoRaPollChannel;

struct LoRaPollChannel {
  PolledNetworkChannel super;
  
  uint16_t local_node_id;
  uint16_t destination_node_id;
  NetworkChannelState state;

  uint8_t receive_buffer[LORA_CHANNEL_BUFFERSIZE];
  uint8_t write_buffer[LORA_CHANNEL_BUFFERSIZE];
  
  FederateMessage output;
  FederatedConnectionBundle* federated_connection;
  void (*receive_callback)(FederatedConnectionBundle* conn, const FederateMessage* msg);
};

/**
 * @brief Initialize a LoRa Network Channel.
 * @param self Pointer to allocated LoRaPollChannel structure.
 * @param local_node_id Identifier for this node.
 * @param destination_node_id Identifier for the target federate node.
 */
void LoRaPollChannel_ctor(LoRaPollChannel* self, uint16_t local_node_id, uint16_t destination_node_id);

/**
 * @brief Non-blocking poll interface for incoming LoRa federated frames.
 */
lf_ret_t LoRaPollChannel_poll(NetworkChannel* untyped_self);

#endif // LORA_CHANNEL_H