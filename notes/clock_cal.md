# Raspberry Pi RP2040 / RP2350 Clock Calculations

## 1. PLL Output Frequency (`FOUTPOSTDIV`)

From the datasheet section **Calculating PLL parameters**:

$$
FOUTPOSTDIV = \frac{FREF}{REFDIV} \times \frac{FBDIV}{POSTDIV1 \times POSTDIV2}
$$

Where:
* **VCO Frequency (`FOUTVCO`):**
  $$
FOUTVCO = \frac{FREF}{REFDIV} \times FBDIV
$$
* **Post-Divider Scaling:**
  $$FOUTPOSTDIV = \frac{FOUTVCO}{POSTDIV1 \times POSTDIV2}$$

---

### Parameter Constraints (RP2350)

* **Reference Input (`FREF / REFDIV`):** Minimum $5\text{ MHz}$
* **VCO Frequency (`FOUTVCO`):** $750\text{ MHz} \le FOUTVCO \le 1600\text{ MHz}$
* **Feedback Divider (`FBDIV`):** $16 \le FBDIV \le 320$
* **Post Dividers (`POSTDIV1`, `POSTDIV2`):** $1 \le POSTDIV1, POSTDIV2 \le 7$

---

## 2. Clock Slice / Generator Output Frequency (`FCLK`)

From the **Clock Generator** architecture section:

$$FCLK = \frac{FSRC}{INT + \frac{FRAC}{256}}$$

Where:
* **`FSRC`:** Input frequency to the clock slice (e.g., `FOUTPOSTDIV` from `PLL_SYS` or `PLL_USB`).
* **`INT`:** Integer divisor (`CLK_x_DIV_INT`).
* **`FRAC`:** 8-bit fractional divisor (`CLK_x_DIV_FRAC`). If unused, set to `0`:
  $$FCLK = \frac{FSRC}{INT}$$
