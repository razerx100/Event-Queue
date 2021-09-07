# Event Queue
My take on a basic event dispatch system. It can handle a single event of one type at a time.

### Instructions
Add subscriber class names in ClassIdentity before using the event queue if the events aren't associated with other events.\

ClassID will be used to sort and make Dispatch() more cache hit friendly for independent events.