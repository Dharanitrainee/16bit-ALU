<h1>16-bit ALU with ESP32 Control Unit</h1>

<p>This project implements a 16-bit Arithmetic Logic Unit (ALU) using TTL (74 series) digital integrated circuits. The control unit is built using an ESP32 microcontroller, enhancing functionality with a user-friendly interface via an OLED display and a rotary encoder for selecting operations.</p>

<blockquote>
  <strong>Disclaimer</strong>: This is my first PCB design, and there may be flaws.This may be the worls worst ALU!. Any feedback or suggestions for improvement are welcome.
</blockquote>

<h2>Features</h2>

<ul>
  <li><strong>Arithmetic Operations</strong>: Addition, Subtraction, Increment, Decrement.</li>
  <li><strong>Logical Operations</strong>: AND, OR, XOR, NOT.</li>
  <li><strong>User Interface</strong>: An OLED display shows the current operation, and a rotary encoder allows for easy selection of operations.</li>
  <li><strong>Control Mechanism</strong>: ESP32 provides control signals and manages data flow within the ALU using shift registers.</li>
</ul>

<h2>Components Used</h2>

<ul>
  <li><strong>TTL ICs (74 series)</strong> for logic implementation</li>
  <li><strong>ESP32 microcontroller</strong> for control signals</li>
  <li><strong>OLED Display (SH1106)</strong> for displaying selected operation and result</li>
  <li><strong>Rotary Encoder (KY-040)</strong> for operation selection</li>
  <li><strong>Shift Registers (74HC595)</strong> for handling input/output</li>
</ul>

<h2>Project Structure</h2>

<ul>
  <li><code>main_code.ino</code>: The primary Arduino code for the ESP32, managing the control signals, encoder input, OLED output, and ALU operations.</li>
  <li><code>images/</code>: Contains bitmaps for icons representing each operation.</li>
  <li><code>README.md</code>: Project documentation.</li>
</ul>

<h2>How It Works</h2>

<ol>
  <li><strong>Control Unit</strong>: The ESP32 microcontroller generates control signals based on user input from the rotary encoder. The OLED screen displays the current operation, input values, and results.</li>
  <li><strong>ALU Operations</strong>: The ALU performs selected operations on 16-bit data, interfaced via shift registers.</li>
  <li><strong>Result Display</strong>: The result of the operation is shown on the OLED display.</li>
</ol>

<h2>Setup and Usage</h2>

<ol>
  <li>Connect the ESP32 to the OLED display and rotary encoder.</li>
  <li>Interface the shift registers with TTL ICs to implement the 16-bit ALU logic.</li>
  <li>Load the Arduino code onto the ESP32.</li>
  <li>Use the rotary encoder to select the desired operation and input values, then view the result on the OLED display.</li>
</ol>

<h2>Future Improvements</h2>

<ul>
  <li>Expand operations to include multiplication and division.</li>
  <li>Optimize the control signal generation for improved speed and accuracy.</li>
  <li>Add support for additional user inputs or controls to expand functionality.</li>
</ul>
