

def add_text(s, ax, loc):
    locs = {'upper right': {'xy': (0.99, 0.99), 'va': 'top', 'ha': 'right'}, 'upper left': {'xy': (0.01, 0.99), 'va': 'top', 'ha': 'left'}, 'lower left': {'xy': (0.01, 0.01), 'va': 'bottom', 'ha': 'left'}, 'lower right': {'xy': (0.99, 0.01), 'va': 'bottom', 'ha': 'right'}}
    assert loc in locs.keys(), f'loc must be in set of : {locs.keys()}'
    fontdic = locs[loc]
    ax.text(*fontdic['xy'], s, va = fontdic['va'], ha = fontdic['ha'], transform= ax.transAxes)
    
