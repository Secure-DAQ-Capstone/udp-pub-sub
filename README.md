# udp-pub-sub

## Files

- `test_role.cpp`: Contains the main function to run the publisher or subscriber based on command-line arguments.

## Testing

main.cpp is used to test the code in udp-pub.cpp and udp-sub.cpp. A make file is created for testing.

```bash

make: Builds all targets.
make clean: Removes the built targets.
make test: Runs the simple test.
make run: Runs the simple test.
make run_pub: Runs the publisher.
make run_sub: Runs the subscriber.
```

## IP Addresses, UDP and Binding

### Binding

- Subscriber: Binds the socket to a local IP address and Port number. This allows the socket to listen for incoming UDP packets on that address and port without polling.
- Publisher: Typically does not need to bind the socket to a specific IP and port. Instead, you specify the destination IP address and port when sending data.
