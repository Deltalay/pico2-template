# Raspberry Pi RP2040 / RP2350 Clock Calculations

## 1. PLL Output Frequency (`FOUTPOSTDIV`)

From the datasheet section **Calculating PLL parameters**:

$$
\text{FOUTPOSTDIV} = \frac{\text{FREF}}{\text{REFDIV}} \times \frac{\text{FBDIV}}{\text{POSTDIV1} \times \text{POSTDIV2}}
$$

Where:

* **VCO Frequency (`FOUTVCO`):**

$$
\text{FOUTVCO} = \frac{\text{FREF}}{\text{REFDIV}} \times \text{FBDIV}
$$

* **Post-Divider Scaling:**

$$
\text{FOUTPOSTDIV} = \frac{\text{FOUTVCO}}{\text{POSTDIV1} \times \text{POSTDIV2}}
$$

---

### Parameter Constraints (RP2350)

* **Reference Input ($\text{FREF} / \text{REFDIV}$):** $\ge 5\text{ MHz}$
* **VCO Frequency ($\text{FOUTVCO}$):** $750\text{ MHz} \le \text{FOUTVCO} \le 1600\text{ MHz}$
* **Feedback Divider ($\text{FBDIV}$):** $16 \le \text{FBDIV} \le 320$
* **Post Dividers ($\text{POSTDIV1}, \text{POSTDIV2}$):** $1 \le \text{POSTDIV1}, \text{POSTDIV2} \le 7$

---

## 2. Clock Slice / Generator Output Frequency (`FCLK`)

From the **Clock Generator** architecture section:

$$
\text{FCLK} = \frac{\text{FSRC}}{\text{INT} + \frac{\text{FRAC}}{256}}
$$

Where:

* **`FSRC`:** Input frequency to the clock slice (e.g., `FOUTPOSTDIV` from `PLL_SYS` or `PLL_USB`).
* **`INT`:** Integer divisor (`CLK_x_DIV_INT`).
* **`FRAC`:** 8-bit fractional divisor (`CLK_x_DIV_FRAC`). If unused, set to `0`:

$$
\text{FCLK} = \frac{\text{FSRC}}{\text{INT}}
$$