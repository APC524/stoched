% Stoched post processing matlab code.
% This script averages the data from n_realizations stoched output files
% and graphs them. It graph these time histories in figure 2. In figure 3,
% it averages time histories together to converge toward the analytical
% solution. In the example code in stoched/examples. The analytical
% solution is that there the number of molecules of A should approach 20.
% Therefore, in figure 3, when enough realizaitons are averaged, the
% solution should approach 20 molecules of A at long times.
clear all
path = './';
fileprefix = 'stoched_output_realization_';
filesuffix = '.txt';
%% plot time histories on same graph
n_realizations = 4;
avg = zeros(3,1);
figure(2)
hold on
for j = 1:n_realizations
    filename = [path,fileprefix,int2str(j),filesuffix];
    d = importdata(filename);
    plot(d.data(:,1),d.data(:,2),'r')
    plot(d.data(:,1),d.data(:,4),'b')
end
h = zeros(2,1)
h(1) = plot(NaN,NaN,'r')
h(2) = plot(NaN,NaN,'b')
set(gca,'FontSize',22)
legend(h, 'A', 'AB')
ylabel('Number of Molecules of A and AB')
xlabel('Time (s)')
title('4 Independent Realizations of a Reaction')

%% average the realizations and plot
n_realizations = 64;
figure(3)
hold on
filename = [path,fileprefix,int2str(1),filesuffix];
d = importdata(filename);
tfinal = 100
sumA = zeros(tfinal,1);
tarray = linspace(1,tfinal,tfinal)';
plotCnt = 1;
colors = ['r','b','m','c','y','g','k','-r']
for j = 1:n_realizations
    filename = [path,fileprefix,int2str(j),filesuffix];
    d = importdata(filename);
    %interpolate A concentration at fixed times
    Aatt=zeros(tfinal,1);
    for t=1:1:tfinal
        i = 1;
        for i = 2:1000
            if d.data(i,1) > t
                break
            end
        end
        i;
        Aatt(t) = (t-d.data(i-1,1))*(d.data(i,2)-d.data(i-1,2))/(d.data(i,1)-d.data(i-1,1))+d.data(i-1,2);
    end
    Aatt;
    sumA = sumA + Aatt;
    if mod(j,8) ==1
        h(plotCnt)= plot(tarray(:),sumA(:)/j,colors(plotCnt),'LineWidth',j/8);
        plotCnt = plotCnt + 1;
        j;
    end
end
set(gca,'FontSize',22)
legend(h,'1 Realization','9 Realizations','17 Realizations','25 Realizations','33 Realizations',...
            '41 Realizations','49 Realizations','57 Realizations')
title('Convergence of Time History with Number of Averaged Realizations')
xlabel('Time (s)')
ylabel('Number of Molecules of A')
%% Make a legend and label the graph
h = zeros(2,1)
h(1) = plot(NaN,NaN,'r')
h(2) = plot(NaN,NaN,'b')
set(gca,'FontSize',22)
legend(h, 'A', 'AB')
ylabel('Number of Molecules of A and AB')
xlabel('Number of Averaged Realizations')
title('Convergence of Number of Molecules with Number of Realizations')
