from os.path import dirname
from os.path import realpath
from os.path import join
import sys

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))
from day5.python.intcode import Intcode


class Network:
    """Network class handling 50 intcode computers"""

    def __init__(self, file):
        """Initialize the intcode computers"""
        self.file = file
        self.nodes = self.initialize_nodes()
        self.NAT = [None, None]
        self.previous_nat_signal = None
        self.first_nat_signal = None

    def initialize_nodes(self):
        """Create 50 intcode computers"""
        return [
            Intcode(self.file, input=input, verbose=False, reset=False)
            for input in range(50)
        ]

    def run(self):

        # Number of nodes
        n_nodes = 50
        # List containing queued inputs for the nodes
        inputs = [[] for x in range(n_nodes)]

        # List to keep track of where each node is sending to
        sending_to = [[] for x in range(n_nodes)]

        # Keep sending messages until breaking condition
        while True:

            # New input list
            sent_input = [[] for x in range(50)]

            # Loop through each node
            for (node, inp, index) in zip(self.nodes, inputs, range(n_nodes)):

                # Wake up the node if we have input
                if node.idle and inp:
                    node.idle = False

                # If node is not idle
                if not node.idle:

                    # Get the output
                    _, output = node(inp)
                    inp = []

                    # If we get an output, then the node is not idle
                    if output is not None:
                        node.idle = False

                        # Manage sending
                        self.manage_sending(
                            sending_to, index, output, sent_input
                        )

            # Update inputs list
            inputs = sent_input

            # If all nodes are idle
            if sum([node.idle for node in self.nodes]) == len(self.nodes):
                # We are done if previous NAT signal is the same
                if self.NAT[1] == self.previous_nat_signal:
                    return self.first_nat_signal, self.NAT[1]
                # Send to node 0
                else:
                    self.previous_nat_signal = self.NAT[1]
                    inputs[0] += self.NAT

    def manage_sending(self, sending_to, index, output, sent_input):
        # Keep track of the output of the node
        sending_to[index].append(output)

        # Check if we have three elements (address, X, Y)
        if len(sending_to[index]) == 3:
            # Check if message is to NAT
            if sending_to[index][0] == 255:
                self.NAT = sending_to[index][1:]
                if self.first_nat_signal is None:
                    self.first_nat_signal = self.NAT[1]
            # Message going to other node
            else:
                # Update the list of sent inputs
                sent_input[sending_to[index][0]] += sending_to[index][1:]
            # Reset the sending signal
            sending_to[index] = []
