from sklearn.linear_model import LinearRegression
def get_lm(xs, ys):
    if xs.ndim == 1: xs = xs.reshape((-1, 1))
    model = LinearRegression().fit(xs, ys)
    intercept, coefficent, r_sq = model.intercept_,model.coef_, model.score(xs, ys)
    return intercept, coefficent, r_sq
