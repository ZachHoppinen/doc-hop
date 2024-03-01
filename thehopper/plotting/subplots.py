# make second row of subplots one big subplot
fig, axes = plt.subplots(3, 3)
gs = axes[0, 1].get_gridspec()
for ax in axes[1, :]: ax.remove()
axbig = fig.add_subplot(gs[1, :])
