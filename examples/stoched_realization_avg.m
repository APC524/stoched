% Stoched post processing matlab code.
% Extracts first value from n_realization output files and average it
% across the realizations. Plot how this average changes as more
% realizaitons are averaged. Recommended usage is to process stoched data
% produced using suppress_print 1 command line option. This only prints the
% final state, so then this script will average the final (equilibrium)
% values
clear all
path = './';
fileprefix = 'stoched_output_realization_';
filesuffix = '.txt';

n_realizations = 4;
avg = zeros(3,1);
figure(2)
hold on
for j = 1:n_realizations
    filename = [path,fileprefix,int2str(j),filesuffix];
    d = importdata(filename);

    for i = 2:size(d.data,2)
        avg(i-1) = (avg(i-1) + d.data(1,i));
    end
    scatter(j,avg(1)/j, 'MarkerEdgeColor', 'r', 'MarkerFaceColor', 'r')
    scatter(j,avg(3)/j, 'MarkerEdgeColor', 'b', 'MarkerFaceColor', 'b')
end

%% label the graph and make a legend
h = zeros(2,1)
h(1) = plot(NaN,NaN,'r')
h(2) = plot(NaN,NaN,'b')
set(gca,'FontSize',22)
legend(h, 'A', 'AB')
ylabel('Number of Molecules of A and AB')
xlabel('Number of Averaged Realizations')
title('Convergence of Number of Molecules with Number of Realizations')
