#!/usr/bin/env python3
"""Exact finite evaluation-layer proxy calibration and held-out regret helpers.

These functions do not select a native plan or enable C03. They use calibration
measurements to interpret existing C02 proxy scores, and never refit on evaluation.
"""
from fractions import Fraction
import math

def require(value,message):
    if not value:raise ValueError(message)
def rational(value):
    require(isinstance(value,(int,Fraction)) and not isinstance(value,bool),'expected exact rational value')
    return Fraction(value)
def ratio(value):
    if value is None:return None
    value=rational(value);return {'numerator':str(value.numerator),'denominator':str(value.denominator)}
def fit_proxy(samples):
    """Nonnegative affine least squares; constant proxies expose missing slope.

    Samples contain training-only proxy values and separately observed calibration
    costs. Nonnegativity is an explicit evaluation assumption, not a native model.
    """
    require(samples,'empty calibration samples');pairs=[(rational(x),rational(y)) for x,y in samples]
    require(all(x>=0 and y>=0 for x,y in pairs),'negative proxy/calibration cost')
    n=len(pairs);xbar=sum((x for x,_ in pairs),Fraction())/n;ybar=sum((y for _,y in pairs),Fraction())/n
    variance=sum(((x-xbar)**2 for x,_ in pairs),Fraction())
    if variance==0:
        intercept=ybar;slope=None;rank=1;status='constant_proxy_intercept_only_slope_unidentified'
    else:
        covariance=sum(((x-xbar)*(y-ybar) for x,y in pairs),Fraction())
        slope=max(Fraction(),covariance/variance);intercept=ybar-slope*xbar
        if intercept<0:
            intercept=Fraction();slope=max(Fraction(),sum((x*y for x,y in pairs),Fraction())/sum((x*x for x,_ in pairs),Fraction()))
        rank=2;status='nonnegative_affine_evaluation_assumption'
    residuals=[intercept+(slope or 0)*x-y for x,y in pairs]
    return {'algorithm':'exact_nonnegative_affine_least_squares_v1','intercept':intercept,'slope':slope,'design_rank':rank,
            'samples':n,'status':status,'calibration_squared_error':sum((e*e for e in residuals),Fraction()),
            'qualification':'evaluation_layer_mapping_only_not_native_policy_or_identified_C03_event_costs'}
def predict(model,value):return model['intercept']+(model['slope'] or 0)*rational(value)
def export_fit(model):
    return {k:ratio(v) if k in ['intercept','slope','calibration_squared_error'] else v for k,v in model.items()}
# Ratios remain exact; RMSE alone converts the mean squared error to floating point.
def error_summary(predicted,actual):
    require(len(predicted)==len(actual) and predicted,'empty/mismatched held-out error samples')
    pairs=[(rational(p),rational(a)) for p,a in zip(predicted,actual)];errors=[p-a for p,a in pairs];n=len(errors)
    absolute=sum((abs(e) for e in errors),Fraction());squared=sum((e*e for e in errors),Fraction())
    relative=[abs(p-a)/a for p,a in pairs if a!=0]
    return {'samples':n,'mean_absolute_error':ratio(absolute/n),'mean_signed_error':ratio(sum(errors,Fraction())/n),
            'mean_squared_error':ratio(squared/n),'root_mean_squared_error':math.sqrt(float(squared/n)),
            'mean_absolute_relative_error':ratio(sum(relative,Fraction())/len(relative)) if relative else None,
            'relative_error_samples':len(relative),'zero_actual_excluded_from_relative_error':n-len(relative),
            'maximum_absolute_error':ratio(max(abs(e) for e in errors))}
def regret(costs,selected,eligible=None):
    require(costs and selected in costs,'selected plan has no measured cost')
    eligible=set(costs) if eligible is None else set(eligible)
    require(eligible and eligible<=set(costs) and selected in eligible,'selected plan is not measured/eligible')
    actual={key:rational(value) for key,value in costs.items()};require(all(v>=0 for v in actual.values()),'negative actual cost')
    best=min(actual[key] for key in eligible);chosen=actual[selected];absolute=chosen-best
    return {'selected':selected,'selected_cost':ratio(chosen),'best_measured_feasible_cost':ratio(best),
            'best_measured_feasible':sorted(key for key in eligible if actual[key]==best),
            'absolute_regret':ratio(absolute),'relative_regret':ratio(absolute/best) if best else None,
            'relative_regret_availability':'available' if best else 'zero_best_cost',
            'measured_feasible_candidates':len(eligible),
            'scope':'retained_verified_and_measured_candidates_under_identical_mode_backend_trace_budget_not_global_cost_optimum'}
def ordering_quality(proxy,costs):
    require(set(proxy)==set(costs),'proxy/measurement candidate sets differ');keys=sorted(proxy);concordant=discordant=proxy_ties=cost_ties=0
    for i,left in enumerate(keys):
        for right in keys[i+1:]:
            px=rational(proxy[left])-rational(proxy[right]);cy=rational(costs[left])-rational(costs[right])
            if px==0:proxy_ties+=1
            if cy==0:cost_ties+=1
            if px and cy:
                if (px>0)==(cy>0):concordant+=1
                else:discordant+=1
    denominator=concordant+discordant
    return {'candidate_pairs':len(keys)*(len(keys)-1)//2,'concordant':concordant,'discordant':discordant,
            'proxy_ties':proxy_ties,'measured_cost_ties':cost_ties,
            'concordance_among_non_ties':ratio(Fraction(concordant,denominator)) if denominator else None,
            'qualification':'finite_proxy_ordering_diagnostic_not_statistical_rank_significance'}
