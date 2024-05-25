import m5
from m5.objects import *

root = Root(full_system=False)

# root.demo = DemoObject()
# root.demo = DemoObject(time_to_wait = '2us')
root.demo = DemoObject(time_to_wait="2us", number_of_fires=3)
root.demo.farewell_object = FarewellObject(buffer_size="100B")

m5.instantiate()

print("Beginning simulation!")

exit_event = m5.simulate()

print(f"Exiting @ tick {m5.curTick()} because {exit_event.getCause()}")
