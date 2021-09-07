# Event Queue
My take on a basic event dispatch system. It can handle a single event of any one type with a single Dispatch().

### Instructions
If the events aren't associated with other events, add subscriber class names in ClassIdentity before using the event queue.

ClassID will be used to sort and make Dispatch() more cache hit friendly for independent events.
