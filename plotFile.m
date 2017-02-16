s10 = 'res10.csv';
s100 = 'res100.csv';
s1000 = 'res1000.csv';
s10000 = 'res10000.csv';
s10_2 = 'res10_2.csv';
s100_2 = 'res100_2.csv';
s1000_2 = 'res1000_2.csv';
s10000_2 = 'res10000_2.csv';

Ms10 = csvread(s10);
Ms100 = csvread(s100);
Ms1000 = csvread(s1000);
Ms10000 = csvread(s10000);

Ms10_2 = csvread(s10_2);
Ms100_2 = csvread(s100_2);
Ms1000_2 = csvread(s1000_2);
Ms10000_2 = csvread(s10000_2);

figure
cdfplot(Ms10)
title('Server 1 Array Size 10')

figure
cdfplot(Ms100)
title('Server 1 Array Size 100')

figure
cdfplot(Ms1000)
title('Server 1 Array Size 1000')

figure
cdfplot(Ms10000)
title('Server 1 Array Size 10000')

figure
cdfplot(Ms10_2)
title('Server 2 Array Size 10')

figure
cdfplot(Ms100_2)
title('Server 2 Array Size 100')

figure
cdfplot(Ms1000_2)
title('Server 2 Array Size 1000')

figure
cdfplot(Ms10000_2)
title('Server 2 Array Size 10000')

fileID = fopen('resultsData.txt','w');

fprintf(fileID,'Server 1 size 10: %.3f\n', mean(Ms10));
fprintf(fileID,'Server 1 size 100: %.3f\n', mean(Ms100));
fprintf(fileID,'Server 1 size 1000: %.3f\n', mean(Ms1000));
fprintf(fileID,'Server 1 size 10000: %.3f\n', mean(Ms10000));

fprintf(fileID,'Server 2 size 10: %.3f\n', mean(Ms10_2));
fprintf(fileID,'Server 2 size 100: %.3f\n', mean(Ms100_2));
fprintf(fileID,'Server 2 size 1000: %.3f\n', mean(Ms1000_2));
fprintf(fileID,'Server 2 size 10000: %.3f\n', mean(Ms10000_2));



