import numpy as np
import pandas as pd
import ROOT

import matplotlib.pyplot as plt
from matplotlib.colors import LogNorm

my_file = "output_sum_1e6.root"
tree_name = "Scoring"

# %%

file = ROOT.TFile.Open(my_file)

tree = file.Get(tree_name)

if not tree:
    raise ValueError("Tree '" + tree_name + "' not found in the file!")

data = {"energy1":[], "energy2":[]}

for entry in tree:
    iEvent = entry.iEvent
    energy1 = entry.energy1 * 1e3
    energy2 = entry.energy2 * 1e3
    
    if energy1 > 0 and energy2 > 0:
        data["energy1"].append(energy1)
        data["energy2"].append(energy2)

file.Close()

# %%

df = pd.DataFrame(data)

histo, ex, ey = np.histogram2d(df["energy1"], df["energy2"],
                               bins = (100, 100),
                               range = [[0, 3e3], [0, 3e3]])

# %%

plt.close('all')

inch_to_mm = 25.4

fig, ax = plt.subplots(figsize=(120/inch_to_mm,100/inch_to_mm))
cax = ax.pcolormesh(ex, ey, histo.T, norm=LogNorm(), 
                    cmap='viridis', rasterized=True)
ax.set_xlabel('Energy 1 (keV)')
ax.set_ylabel('Energy 2 (keV)')
plt.tight_layout(pad=0.5)

save_name = "output_sum_coincidence_plot"
plt.savefig(f"{save_name}.pdf")
plt.savefig(f"{save_name}.jpg", dpi=600)
